/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 15:29:32 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/02/03 15:42:14 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philostatus(t_philo *philo, char *routine)
{
	if (finish(philo))
		return ;
	pthread_mutex_lock(&philo->arg->death_signal);
	printf("%zu		%d %s\n", (get_time_micro()/1000 - philo->arg->time_start/1000), philo->philo_num, routine);
	//printf("%llu 		%d %s\n", get_current_time() - philo->arg->time_start/1000,  philo->philo_num + 1, routine);
	pthread_mutex_unlock(&philo->arg->death_signal);
	
}

void sleep_philo(t_philo *philo)
{
	philostatus(philo, "sleeping");
	mysleep(philo->arg->time_to_sleep * 1000);

}

void think_philo(t_philo *philo)
{
	philostatus(philo, "thinking");
}

void	check_fork(t_philo *philo, int fork)
{
	
	while(!finish(philo))
	{
		pthread_mutex_lock(&(philo->arg->forks[fork]));
		if (philo->arg->fork[fork] == 0)
		{
			philo->arg->fork[fork] = 1;
			pthread_mutex_unlock(&philo->arg->forks[fork]);
			break ;
		}
		pthread_mutex_unlock(&philo->arg->forks[fork]);
	}
}

void	drop_fork(t_philo *philo, int fork)
{
	
	while(!finish(philo))
	{
		pthread_mutex_lock(&philo->arg->forks[fork]);
		if (philo->arg->fork[fork] == 1)
		{
			philo->arg->fork[fork] = 0;
			pthread_mutex_unlock(&philo->arg->forks[fork]);
			break ;
		}
		pthread_mutex_unlock(&philo->arg->forks[fork]);
	}
}

void	eat_count(t_philo *philo)
{
	philo->eat_counter++;
	if (philo->eat_counter == philo->arg->eat_count)
	{
		pthread_mutex_lock(&philo->arg->eat_count_lock);
		philo->arg->eat_count++;
		pthread_mutex_unlock(&philo->arg->eat_count_lock);
	}
}

void eat_philo(t_philo *philo)
{	
	check_fork(philo, philo->forkright);
	philostatus(philo, "takes right fork");
	check_fork(philo, philo->forkleft);
	philostatus(philo, "takes left fork");
	pthread_mutex_lock(&philo->arg->death_signal);
	philo->time_last_ate = get_time_micro();
	pthread_mutex_unlock(&philo->arg->death_signal);
	philostatus(philo, "is eating");
	mysleep(philo->arg->time_to_eat*1000);
	drop_fork(philo, philo->forkright);
	drop_fork(philo, philo->forkleft);
}

void *philo_routine(void *s)
{
	t_philo *philo;

	philo = (t_philo *)(s);
	if (philo->philo_num % 2 == 0)
		usleep(1000);
	while(!finish(philo))
	{
		eat_philo(philo);
		sleep_philo(philo);
		think_philo(philo);
	}
	return 0;
}