/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 15:29:32 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/01/26 14:41:29 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philostatus(t_philo *philo, char *routine)
{
	if (philo->arg->finish == 1)
		return ;
	pthread_mutex_lock(&philo->arg->death_signal);
	printf("%d is %s\n", philo->philo_num, routine);
	pthread_mutex_unlock(&philo->arg->death_signal);
}

void sleep_philo(t_philo *philo)
{

	if (philo->arg->finish == 1)
		return ;
	pthread_mutex_lock(&philo->arg->death_signal);
	pthread_mutex_unlock(&philo->arg->death_signal);
	//check of iemand dood is dan pas printen.
	printf("%d is sleeping %d micros\n", philo->philo_num, philo->arg->time_to_sleep * 1000);
	mysleep(philo->arg->time_to_sleep * 1000);
}

void think_philo(t_philo *philo)
{
	if (philo->arg->finish == 1)
		return ;
	pthread_mutex_lock(&philo->arg->death_signal);
	pthread_mutex_unlock(&philo->arg->death_signal);
	printf("%d is thinking %lu timetodie\n", philo->philo_num, (get_time_micro()-philo->time_last_ate));
}

void eat_philo(t_philo *philo)
{
	//pthread_mutex_lock(&philo->arg->forks);
	while (1)
	{
		
		if (philo->arg->fork[philo->forkright] == 1)
		{
			printf("%d philo %lu dying in right %d left %d\n", philo->philo_num, (get_time_micro() - philo->time_last_ate), philo->arg->fork[philo->forkleft], philo->arg->fork[philo->forkright]);
			usleep(100);
		}
		else
		{
			//printf("%d philo %lu dying in right %d left %d\n", philo->philo_num, (get_time_micro() - philo->time_last_ate),philo->arg->fork[philo->forkleft], philo->arg->fork[philo->forkright]);
			pthread_mutex_lock(&philo->arg->forks[philo->forkright]);
			philo->arg->fork[philo->forkright] = 1;
			pthread_mutex_lock(&philo->arg->forks[philo->forkleft]);	
			philo->arg->fork[philo->forkleft] = 1;
			pthread_mutex_lock(&philo->arg->death_signal);
			pthread_mutex_unlock(&philo->arg->death_signal);
			philo->time_last_ate = get_time_micro();
			printf("%d is eating   %lu timetodie\n", philo->philo_num, (get_time_micro()-philo->time_last_ate) + philo->arg->time_to_die*1000);
			mysleep(philo->arg->time_to_eat*1000);
			philo->arg->fork[philo->forkright] = 0;
			philo->arg->fork[philo->forkleft] = 0;
			pthread_mutex_unlock(&philo->arg->forks[philo->forkright]);
			pthread_mutex_unlock(&philo->arg->forks[philo->forkleft]);
			break ;
		}
	}
	//printf("%d is eating\ncurrenttime=%zu\ntimelastate=%zu\n", philo->philo_num, get_time_micro(), philo->time_last_ate);	
	//philo->time_last_ate = get_time_micro() / 1000
	//pthread_mutex_unlock(&philo->arg->forks);
}

void	check_death(t_philo *philo)
{
	if (get_time_micro() - philo->time_last_ate > (size_t)(philo->arg->time_to_die * 1000))
		{
			printf("if %zu > %zu \n", get_time_micro() - philo->time_last_ate, (size_t)(philo->arg->time_to_die * 1000));
			philo->arg->finish = 1;
			pthread_mutex_lock(&philo->arg->death_signal);
			printf("philo %d is dead\n", philo->philo_num);
			exit(1);
		}
}

void	death_checker(t_philo *philo, t_arg *arg)
{
	int i;

	printf("alive philo num%d\n", philo->philo_num);
	while (arg->finish == 0)
	{
		mysleep(900);
		i = 0;
		while (i < philo->arg->philo_num)
		{
			check_death(&philo[i]);
			i++;
		}
	}

	printf("alive philo num %d\n", philo->philo_num);
	//if (philo->time_last_ate )
}

void *philo_routine(void *s)
{
	t_philo *philo;

	philo = (t_philo *)(s);
	philo->arg->finish = 0;
	//print_all(philo);
	while(philo->arg->finish == 0)
	{
		eat_philo(philo);
		philostatus(philo, "sleeping");
		mysleep(philo->arg->time_to_sleep);
		printf("philo %d and  %zu > %zu \n", philo->philo_num, get_time_micro() - philo->time_last_ate, (size_t)(philo->arg->time_to_die * 1000));
		philostatus(philo, "thinking");
		//sleep_philo(philo);
		//think_philo(philo);		
	}
	return NULL;
}