/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 13:40:38 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/02/17 16:06:08 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_fork(t_philo *philo, int fork)
{

		pthread_mutex_lock(&(philo->arg->forks[fork]));
		if (philo->arg->fork[fork] == 0)
		{
			philo->arg->fork[fork] = 1;
		}

}

void	drop_fork(t_philo *philo, int fork)
{

		if (philo->arg->fork[fork] == 1)
			philo->arg->fork[fork] = 0;
		pthread_mutex_unlock(&philo->arg->forks[fork]);
	
}

void	eat_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->eat_count_lock);
	philo->eat_counter++;
	if (philo->eat_counter == philo->arg->number_must_eat)
		philo->arg->eat_count++;
	pthread_mutex_unlock(&philo->arg->eat_count_lock);
}
