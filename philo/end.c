/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   end.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/30 14:36:32 by dyeboa        #+#    #+#                 */
/*   Updated: 2024/06/03 16:56:41 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

void	end_philos(t_philo *philo, pthread_t *thread, t_arg *arg)
{
	int	i;

	i = -1;
	while (++i < philo->arg->philo_num )
		pthread_join(thread[i], NULL);
	i = -1;
	while (++i < philo->arg->philo_num )
	{
		pthread_mutex_destroy(&philo->arg->forks[i]);
		pthread_mutex_destroy(&philo[i].is_finish);
	}
	if (philo->arg->philo_num == 1)
		pthread_mutex_destroy(&philo->arg->forks[1]);
	pthread_mutex_destroy(&arg->death_signal);
	pthread_mutex_destroy(&arg->eat_count_lock);
	pthread_mutex_destroy(&arg->create);
	free(arg->fork);
	free(arg->forks);
	free(arg);
	free(philo);
	free(thread);
}

void	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->eat_count_lock);
	if (philo->arg->eat_count > 0)
	{
		if (philo->arg->eat_count >= philo->arg->philo_num)
		{
			pthread_mutex_lock(&philo->arg->death_signal);
			printf("%zu\t%d %s\n", (get_time_micro() / 1000 - \
			philo->arg->time_start / 1000), philo->philo_num, "We ate enough"\
			" required times, but we want some more please");
			philo->arg->finish = 1;
			pthread_mutex_unlock(&philo->arg->death_signal);
		}
	}
	pthread_mutex_unlock(&philo->arg->eat_count_lock);
	pthread_mutex_lock(&philo->arg->death_signal);
	if (get_time_micro() - philo->time_last_ate > \
	(size_t)philo->arg->time_to_die * 1000)
	{
		printf("%zu\t%d %s\n", (get_time_micro() / 1000 - \
		philo->arg->time_start / 1000), philo->philo_num, "died");
		philo->arg->finish = 1;
	}
	pthread_mutex_unlock(&philo->arg->death_signal);
}

void	death_checker(t_philo *philo)
{
	int	i;

	while (philo->arg->finish == 0)
	{
		i = 0;
		while (philo->arg->finish == 0 && i < philo->arg->philo_num)
		{
			check_death(&philo[i]);
			i++;
		}
		mysleep(100);
	}
}
