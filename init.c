/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/10 15:28:33 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/01/10 15:29:20 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int init_struct(t_arg *arg, int argc, char **argv)
{
	arg->philo_num = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg->number_must_eat = ft_atoi(argv[5]);
	else
		arg->number_must_eat = 0;
	arg->time_start = (get_time_micro()/1000);
	// arg->forks = malloc(sizeof(pthread_mutex_t) * arg->philo_num);
	if (arg->philo_num < 1 || arg->time_to_die < 1 || arg->time_to_eat < 1 \
		|| arg->time_to_sleep < 1 || arg->number_must_eat < 0)
		return (1);
	//printf("init struct num = %d die = %d, eat = %d sleep = %d start = %zu \n", arg->philo_num, arg->time_to_die, arg->time_to_eat, arg->time_to_sleep, arg->time_start);
	//printf("init struct\n");
	return (0);
}

t_philo *init_philo(t_arg *arg, char **argv)
{
	t_philo 	*philo;
	int i;
	int num;

	i = 0;
	num = ft_atoi(argv[1]);
	arg->philo_num = num;
	philo = malloc(num * sizeof(t_philo));
	if(!philo)
	{
		printf("init_philo malloc");
		return (NULL);
	}
	while (i < num)
	{
		if (i == 0)
			philo[i].forkright = num - 1;
		else
			philo[i].forkright = i  -1;
		philo[i].philo_num = i;
		philo[i].forkleft = i;
		philo[i].time_last_ate = get_time_micro();
		printf("%zu\n", philo[i].time_last_ate);
		philo[i].eat_count = 0;
		philo[i].arg = arg;
		i++;
	}
	printf("init philo\n");
	return (philo);
}