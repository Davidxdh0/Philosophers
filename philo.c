/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 15:29:32 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/01/18 18:16:11 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void sleep_philo(t_philo *philo)
{

	if (philo->arg->finish == 1)
		return ;
	pthread_mutex_lock(&philo->arg->death_signal);
	pthread_mutex_unlock(&philo->arg->death_signal);
	//check of iemand dood is dan pas printen.
	printf("%d is sleeping %d micros \n", philo->philo_num, philo->arg->time_to_sleep * 1000);
	printf("%d philo %lu dying in right %d left %d\n", philo->philo_num, (get_time_micro() - philo->time_last_ate),philo->arg->fork[philo->forkleft], philo->arg->fork[philo->forkright]);
	mysleep(philo->arg->time_to_sleep * 1000);
}

void think_philo(t_philo *philo)
{
	if (philo->arg->finish == 1)
		return ;
	pthread_mutex_lock(&philo->arg->death_signal);
	pthread_mutex_unlock(&philo->arg->death_signal);
	//check of iemand dood is dan pas printen met philo->arg-?timetot
	printf("%d is thinking\n", philo->philo_num);
	printf("%d philo %lu dying in right %d left %d\n", philo->philo_num, (get_time_micro() - philo->time_last_ate), philo->arg->fork[philo->forkleft], philo->arg->fork[philo->forkright]);
	
}

void eat_philo(t_philo *philo)
{
	//pthread_mutex_lock(&philo->arg->forks);
	while (1)
	{
		
		if ( philo->arg->fork[philo->forkright] == 1)
		{
			printf("%d philo %lu dying in right %d left %d\n", philo->philo_num, (get_time_micro() - philo->time_last_ate), philo->arg->fork[philo->forkleft], philo->arg->fork[philo->forkright]);
			usleep(100);
		}
		else
		{
			//printf("%d philo %lu dying in right %d left %d\n", philo->philo_num, (get_time_micro() - philo->time_last_ate),philo->arg->fork[philo->forkleft], philo->arg->fork[philo->forkright]);
			pthread_mutex_lock(&philo->arg->forks[philo->forkright]);
			pthread_mutex_lock(&philo->arg->forks[philo->forkleft]);
			philo->arg->fork[philo->forkright] = 1;
			philo->arg->fork[philo->forkleft] = 1;
			pthread_mutex_lock(&philo->arg->death_signal);
			pthread_mutex_unlock(&philo->arg->death_signal);
			philo->time_last_ate = get_time_micro();
			printf("%d is eating & timetodie = %lu ", philo->philo_num, philo->arg->time_to_die*1000 - ((get_time_micro()-philo->time_last_ate)));
			printf("timetoeat %d\n", philo->arg->time_to_eat);
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
	// printf("finish = %d\n", philo->arg->finish);

	//print_all(philo);
	while(philo->arg->finish == 0)
	{
		// mutexen
		// if (get_time_micro() - philo->arg->time_start > 5000000)
		// 	//printf("%zu\n%zu\n", get_time_micro(), philo->arg->time_start );
		// 	 philo->arg->finish = 1;
		eat_philo(philo);
		sleep_philo(philo);
		think_philo(philo);		
	}
	//printf("finished %d, philo %d\n", philo->arg->finish, philo->philo_num);
	return NULL;
}