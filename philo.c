/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 15:29:32 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/01/31 15:00:58 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philostatus(t_philo *philo, char *routine)
{
	pthread_mutex_lock(&philo->arg->death_signal);
	printf("%zu		%d %s\n", (get_time_micro() - philo->arg->time_start)/1000, philo->philo_num + 1, routine);
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
	if(philo->arg->finish == 0)
	{
		pthread_mutex_lock(&philo->arg->forks[fork]);
		if (philo->arg->fork[fork] == 0)
		{
			philo->arg->fork[fork] = 1;
			pthread_mutex_unlock(&philo->arg->forks[fork]);
			return ;
		}
		pthread_mutex_unlock(&philo->arg->forks[fork]);
	}
}

void eat_philo(t_philo *philo)
{	
	pthread_mutex_lock(&philo->arg->forks[philo->forkright]);
	philostatus(philo, "takes right fork");
	//philo->arg->fork[philo->forkright] = 1;
	pthread_mutex_lock(&philo->arg->forks[philo->forkleft]);
	philostatus(philo, "takes left fork");
	//philo->arg->fork[philo->forkleft] = 1;
	philo->time_last_ate = get_time_micro();
	philostatus(philo, "is eating");
	mysleep(philo->arg->time_to_eat*1000);
	//p_sleep(philo->arg, philo->arg->time_to_eat);
	//philo->arg->fork[philo->forkright] = 0;
	//philo->arg->fork[philo->forkleft] = 0;
	pthread_mutex_unlock(&philo->arg->forks[philo->forkright]);
	pthread_mutex_unlock(&philo->arg->forks[philo->forkleft]);
}

void *philo_routine(void *s)
{
	t_philo *philo;

	philo = (t_philo *)(s);
	if (philo->philo_num % 2 == 0)
		usleep(100);
	while(!finish(philo))
	{
		eat_philo(philo);
		sleep_philo(philo);
		think_philo(philo);
	}
	return 0;
}