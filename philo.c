/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 15:29:32 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/01/11 15:20:55 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void sleep_philo(t_philo *philo)
{
	//check of iemand dood is dan pas printen.
	printf("%d is sleeping %d ms \n", philo->philo_num, philo->arg->time_to_sleep);
	usleep(philo->arg->time_to_sleep * 1000);
}

void think_philo(t_philo *philo)
{
	//check of iemand dood is dan pas printen met philo->arg-?timetot
	printf("%d is thinking\n", philo->philo_num);
}

void eat_philo(t_philo *philo)
{
	//pthread_mutex_lock(&philo->arg->forks);

	printf("%d is eating\n", philo->philo_num);
	usleep(philo->arg->time_to_eat*1000);
	philo->time_last_ate = get_time_micro();

	//printf("%d is eating\ncurrenttime=%zu\ntimelastate=%zu\n", philo->philo_num, get_time_micro(), philo->time_last_ate);	
	//philo->time_last_ate = get_time_micro() / 1000
	//pthread_mutex_unlock(&philo->arg->forks);
}

void	check_death(t_philo *philo)
{
	long current;
	long verschil;
	current = get_time_micro();
	verschil = current - philo->time_last_ate;
	printf("death %ld verschil", verschil);
	if (verschil >= philo->arg->time_to_die * 1000000)
		{
			philo->arg->finish = 1;
			printf("dead %d\n", philo->philo_num);
		}

}
void	death_checker(t_philo *philo, t_arg *arg)
{
	int i;

	i = 0;
	while (arg->finish == 0)
	{
		usleep(2000);
		while (i < philo->philo_num)
		{
			check_death(&philo[i]);
			i++;
		}
	}

	printf("alive philo num%d\n", philo->philo_num);
	//if (philo->time_last_ate )
}

void *philo_routine(void *s)
{
	t_philo *philo;

	philo = (t_philo *)(s);
	philo->arg->finish = 0;
	printf("finish = %d\n", philo->arg->finish);
	
	//print_all(philo);
	while(philo->arg->finish == 0)
	{
		// mutexen
		if (get_time_micro() - philo->arg->time_start > 2000000)
			//printf("%zu\n%zu\n", get_time_micro(), philo->arg->time_start );
			 philo->arg->finish = 1;
		eat_philo(philo);
		sleep_philo(philo);
		think_philo(philo);		
	}
	printf("finished %d\n", philo->arg->finish);
	return NULL;
}