/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/30 14:36:32 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/02/03 15:49:31 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	end_philos(t_philo *philo, pthread_t *thread, t_arg *arg)
{
	int i;

	i = -1;
	while(++i < philo->arg->philo_num)
	{
		pthread_join(thread[i], NULL);
	}
	i = -1;
	while(++i < philo->arg->philo_num)
	{
		pthread_mutex_destroy(&philo->arg->forks[i]);
	}
	pthread_mutex_destroy(&arg->death_signal);	
	pthread_mutex_destroy(&arg->eat_count_lock);	
}

void	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->death_signal);
	if (get_time_micro() - philo->time_last_ate > (size_t)(philo->arg->time_to_die * 1000))
		{
			pthread_mutex_unlock(&philo->arg->death_signal);
			philostatus(philo, "died");
			pthread_mutex_lock(&philo->arg->death_signal);
			philo->arg->finish = 1;
			pthread_mutex_unlock(&philo->arg->death_signal);
		}
	else
		pthread_mutex_unlock(&philo->arg->death_signal);
}

int	finish(t_philo *philo)
{
	int i;

	i = 0;
	pthread_mutex_lock(&philo->arg->death_signal);
	i = philo->arg->finish;
	pthread_mutex_unlock(&philo->arg->death_signal);
	return (i);
}

void	death_checker(t_philo *philo)
{
	int i;
	
	while (!finish(philo))
	{
		usleep(50);
		i = 0;
		while (!finish(philo) && i < philo->arg->philo_num)
		{
			check_death(&philo[i]);
			i++;
		}
	}
}
