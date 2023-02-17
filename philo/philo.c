/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 15:29:32 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/02/17 17:32:26 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philostatus(t_philo *philo, char *routine)
{
	//pthread_mutex_lock(&philo->is_finish);
	// if (philo->finished == 1)
	// 	return (0);
	if(finish(philo))
		return (0);
	//pthread_mutex_unlock(&philo->is_finish);
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

void	*philo_routine(void *s)
{
	t_philo	*philo;

	philo = (t_philo *)(s);
	if (philo->philo_num % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (!eat_philo(philo))
			break ;
		if (!sleep_philo(philo))
			break ;
		if (!think_philo(philo))
			break ;
	}
	return (0);
}
