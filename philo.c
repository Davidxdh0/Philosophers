/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 15:29:32 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/01/10 15:41:08 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void sleep_philo(t_philo *philo)
{
	printf("%d is sleeping %d microseconds \n", philo->philo_num, philo->arg->time_to_sleep);
	usleep(philo->arg->time_to_sleep *1000);
}

void think_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->forks);
	printf("%d is thinking\n", philo->philo_num);	
	pthread_mutex_unlock(&philo->arg->forks);
}

void eat_philo(t_philo *philo)
{
	printf("%d is eating\n", philo->philo_num);	
}

void *philo_routine(void *s)
{
	t_philo *philo;

	philo = (t_philo *)(s);
	//printf("routine num = %d die = %d, eat = %d sleep = %d \n", philo->philo_num,  philo->arg->time_to_die,  philo->arg->time_to_eat,  philo->arg->time_to_sleep);
	while(1)
	{
		// mutexen
		eat_philo(philo);
		sleep_philo(philo);
		think_philo(philo);
	}
	return NULL;
}