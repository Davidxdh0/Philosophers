/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 15:30:45 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/02/25 21:01:30 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

static int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

int	ft_atoi(const char *str)
{
	int			i;
	int			minorplus;
	int			number;

	number = 0;
	i = 0;
	minorplus = 1;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minorplus *= -1;
		i++;
		if (str[i] == '-' || str[i] == '+')
			return (0);
	}
	while ((str[i]) >= '0' && str[i] <= '9')
	{
		number *= 10;
		number += (str[i] - '0');
		i++;
	}
	return (number * minorplus);
}

size_t	get_time_micro(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void	mysleep(useconds_t time)
{
	long long	timestart;

	timestart = get_time_micro();
	while (get_time_micro() - timestart < time)
		usleep(200);
}

int	create_threads(pthread_t *thread, t_arg *arg, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&arg->create);
	arg->created = 0;
	while (i < arg->philo_num)
	{
		arg->time_start = get_time_micro();
		if (pthread_create(&thread[i], NULL, philo_routine, &philo[i]))
		{
			printf("create threads fails");
			pthread_mutex_unlock(&arg->create);
			return (0);
		}
		i++;
		arg->created = i;
		usleep(250);
	}
	arg->time_start = get_time_micro();
	pthread_mutex_unlock(&arg->create);
	return (1);
}
