/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 15:29:32 by dyeboa        #+#    #+#                 */
/*   Updated: 2024/06/03 18:17:01 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philostatus(t_philo *philo, char *routine)
{
	pthread_mutex_lock(&philo->arg->death_signal);
	if (philo->arg->finish)
	{
		pthread_mutex_unlock(&philo->arg->death_signal);
		return (0);
	}
	printf("%zu\t%d %s\n", (get_time_micro() / 1000 - \
	philo->arg->time_start / 1000), philo->philo_num, routine);
	pthread_mutex_unlock(&philo->arg->death_signal);
	return (1);
}

int	sleep_philo(t_philo *philo)
{
	int	i;

	i = philostatus(philo, "is sleeping");
	mysleep(philo->arg->time_to_sleep * 1000);
	return (i);
}

int	think_philo(t_philo *philo)
{
	int	i;

	i = philostatus(philo, "is thinking");
	return (i);
}

void	pickup_forks(t_philo *philo)
{
	if (philo->forkleft < philo->forkright && philo->arg->philo_num > 1)
	{
		pthread_mutex_lock(&(philo->arg->forks[philo->forkleft]));
		pthread_mutex_lock(&(philo->arg->forks[philo->forkright]));
	} 
	else if (philo->arg->philo_num > 1)
	{
		pthread_mutex_lock(&(philo->arg->forks[philo->forkright]));
		pthread_mutex_lock(&(philo->arg->forks[philo->forkleft]));
	}
	else
		pthread_mutex_lock(&(philo->arg->forks[philo->forkright]));
}

int	eat_philo(t_philo *philo)
{	
	int	i;

	pickup_forks(philo);
	philostatus(philo, "has taken a fork");
	if (philo->arg->philo_num == 1)
	{
		mysleep(philo->arg->time_to_die * 1000);
		pthread_mutex_unlock(&philo->arg->forks[philo->forkright]);
		return (0);
	}
	philostatus(philo, "has taken a fork");
	pthread_mutex_lock(&philo->arg->death_signal);
	philo->time_last_ate = get_time_micro();
	pthread_mutex_unlock(&philo->arg->death_signal);
	i = philostatus(philo, "is eating");
	mysleep(philo->arg->time_to_eat * 1000);
	eat_count(philo);
	pthread_mutex_unlock(&philo->arg->forks[philo->forkright]);
	pthread_mutex_unlock(&philo->arg->forks[philo->forkleft]);
	return (i);
}

void	*philo_routine(void *s)
{
	t_philo	*philo;

	philo = (t_philo *)(s);
	if (thread_creation_check(philo) == 0)
		return (NULL);
	pthread_mutex_lock(&philo->arg->death_signal);
	philo->arg->fork[philo->forkright] = 0;
	philo->arg->fork[philo->forkleft] = 0;
	philo->time_last_ate = get_time_micro();
	pthread_mutex_unlock(&philo->arg->death_signal);
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
