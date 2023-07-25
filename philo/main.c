/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/05 20:08:30 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/02/25 21:01:01 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		j = 0;
		if (ft_atoi(argv[i]) <= 0)
		{
			printf("Not valid input\n");
			return (0);
		}
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("wrong %c [i = %d][j = %d", argv[i][j], i, j);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

// void	leakss()
// {
// 	system("leaks philosopher");
// }

// atexit(leakss);

int	main(int argc, char **argv)
{
	t_arg		*arg;
	t_philo		*philo;
	pthread_t	*thread;

	if (argc != 5 && argc != 6)
	{
		printf("Argument count is not 4 or 5\n");
		return (1);
	}
	if (!check_input(argc, argv))
		return (1);
	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (1);
	thread = malloc(arg->philo_num * sizeof(pthread_t));
	if (!thread)
		return (1);
	philo = init_philo(arg, argv);
	if (!philo)
		return (1);
	if (!init_struct(arg, argc, argv) || !create_threads(thread, arg, philo))
		return (1);
	death_checker(philo);
	end_philos(philo, thread, arg);
	return (0);
}
