/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/05 20:08:30 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/01/11 14:54:18 by dyeboa        ########   odam.nl         */
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
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("fout %c [i = %d][j = %d",argv[i][j], i, j);
				return(1);
			}
			j++;
		}
		i++;
	}
	printf("input is correct\n");
	return (0);
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
	if (!arg || check_input(argc, argv))
		return (1);
	// allocate memory
	philo = init_philo(arg, argv);
	if (!philo)
		return(1);
	if (init_struct(arg, argc, argv))
		return(1);
	thread = malloc(arg->philo_num * sizeof(pthread_t));
	if(!thread)
		return(1);
	//printf("philo num = %d die = %d, eat = %d sleep = %d \n", philo->arg->philo_num,  philo->arg->time_to_die,  philo->arg->time_to_eat,  philo->arg->time_to_sleep);
	//maak threads van philo's en stuur door naar philo
	printf("begin eten/slapen/denken\n");
	if (create_threads(thread, arg, philo))
		return (1);
	death_checker(philo);
	printf("dood of free'en\n");
	//
	

	
	//Begin eten
	return (0);
}
