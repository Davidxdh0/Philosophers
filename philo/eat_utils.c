/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/06 13:40:38 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/03/02 10:56:58 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->eat_count_lock);
	philo->eat_counter++;
	if (philo->eat_counter == philo->arg->number_must_eat)
		philo->arg->eat_count++;
	pthread_mutex_unlock(&philo->arg->eat_count_lock);
}

int	thread_creation_check(t_philo *philo)
{
	int	created;

	pthread_mutex_lock(&philo->arg->create);
	created = philo->arg->created;
	pthread_mutex_unlock(&philo->arg->create);
	if (created != philo->arg->philo_num)
		return (0);
	return (1);
}
