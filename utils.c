/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 15:30:45 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/01/18 18:09:17 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

// {
//  time_t       tv_sec;   /* seconds since Jan. 1, 1970 */
// 	suseconds_t  tv_usec;  /* MICROseconds */
//  };
size_t	get_time_micro()
{
	struct timeval time ;

	gettimeofday(&time, NULL);
	return(time.tv_sec * 1000000 + time.tv_usec);
}

void	mysleep(useconds_t time)
{
	size_t timestart;
	
	timestart = get_time_micro();
	// printf("mysleep %zu\n", time);
	while(get_time_micro() - timestart < time)
		usleep(1);
}


int	create_threads(pthread_t *thread, t_arg *arg, t_philo *philo)
{
	int i;
	
	i = 0;
	while (i < arg->philo_num)
	{
		if (pthread_create(&thread[i], NULL, &philo_routine, &philo[i]))
		{
			printf("create threads faalt");
			return (1);
		}
		i++;
	}
	return (0);
}

void	print_all(t_philo *philo)
{
	printf("phil num  %d \n", philo->arg->philo_num);
	printf("eat count %d \n", philo->eat_count);
	printf("fork left %d \n", philo->forkleft);
	printf("fork righ %d \n", philo->forkright);
	printf("philo num %d \n", philo->philo_num);
	printf("tlasteat  %zu \n", philo->time_last_ate);

	// printf("%d \n", philo->arg->death_signal);
	printf("eat cnt %d \n", philo->arg->eat_cnt);
	printf("finish  %d \n", philo->arg->finish);
	// printf("%d \n", philo->arg->fork);
	// printf("%d \n", philo->arg->forks);

	printf("musteat %d \n", philo->arg->number_must_eat);
	printf("tstart  %zu \n", philo->arg->time_start);
	printf("t_todie %d \n", philo->arg->time_to_die);
	printf("tteat   %d \n", philo->arg->time_to_eat);
	printf("ttsleep %d \n\n", philo->arg->time_to_sleep);
}