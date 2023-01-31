/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/05 20:08:30 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/01/31 11:55:20 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_input(int argc, char **argv)
{
	int i;
	int j;

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
				printf("fout %c [i = %d][j = %d",argv[i][j], i, j);
				return(0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_arg		*arg;
	t_philo	 	*philo;
	pthread_t	*thread;

	if (argc != 5 && argc != 6)
	{
		printf("Argument count is not 4 or 5\n");
		return (1);
	}
	arg = malloc(sizeof(t_arg));
	if (!arg || !check_input(argc, argv))
		return (1);
	philo = init_philo(arg, argv);
	if (!philo)
		return(1);
	if (!init_struct(arg, argc, argv))
		return(1);
	thread = malloc(arg->philo_num * sizeof(pthread_t));
	if(!thread)
		return(1);
	if (!create_threads(thread, arg, philo))
		return (1);

	return (0);
}
