/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 15:29:32 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/02/24 11:33:01 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philostatus(t_philo *philo, char *routine)
{
	if(finish(philo))
		return (0);
	pthread_mutex_lock(&philo->arg->death_signal);
	printf("%zu\t%d %s\n", (get_time_micro() / 1000 - \
	philo->arg->time_start / 1000), philo->philo_num, routine);
	pthread_mutex_unlock(&philo->arg->death_signal);
	return (1);
}

int	sleep_philo(t_philo *philo)
{
	int i;
	
	i = philostatus(philo, "sleeping");
	mysleep(philo->arg->time_to_sleep * 1000);
	return (i);
}

int	think_philo(t_philo *philo)
{
	int i;

	i = philostatus(philo, "thinking");
	return (i);

}

int	eat_philo(t_philo *philo)
{	
	int i;

	check_fork(philo, philo->forkright);
	philostatus(philo, "takes right fork");
	if (philo->arg->philo_num == 1)
	{
		mysleep(philo->arg->time_to_die * 1000);
		return (0);
	}	
	check_fork(philo, philo->forkleft);
	philostatus(philo, "takes left fork");
	pthread_mutex_lock(&philo->arg->death_signal);
	philo->time_last_ate = get_time_micro();
	pthread_mutex_unlock(&philo->arg->death_signal);
	i = philostatus(philo, "is eating");
	mysleep(philo->arg->time_to_eat * 1000);
	eat_count(philo);
	drop_fork(philo, philo->forkright);
	drop_fork(philo, philo->forkleft);
	return(i);
}

int	thread_creation_check(t_philo *philo)
{
	int	created;

	pthread_mutex_lock(&philo->arg->create);
	created = philo->arg->created;
	pthread_mutex_unlock(&philo->arg->create);
	if (created != philo->arg->philo_num)
		return (0);
	return (1);
}

void	*philo_routine(void *s)
{
	t_philo	*philo;

	philo = (t_philo *)(s);
	if (thread_creation_check(philo) == 0)
		return (NULL);
	//pthread_mutex_lock(&philo->meal_time_mutex);
	philo->time_last_ate = get_time_micro();
	//pthread_mutex_unlock(&philo->meal_time_mutex);
	if (philo->philo_num % 2 == 0)
		usleep(100);
	while (1)
	{
		if (!eat_philo(philo))
			break ;
		if (!sleep_philo(philo))
			break ;
		if (!think_philo(philo))
			break ;
	}
	return (NULL);
}
