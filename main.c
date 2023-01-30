/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/05 20:08:30 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/01/30 14:32:43 by dyeboa        ########   odam.nl         */
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

void	end_philos(t_philo *philo, pthread_t *thread, t_arg *arg)
{
	int i;

	i = -1;
	while(++i < philo->arg->philo_num)
	{
		//pthread_join(thread[i], NULL);
		pthread_detach(thread[i]);
	}
	i = -1;
	while(++i < philo->arg->philo_num)
	{
		pthread_mutex_destroy(&philo->arg->forks[i]);
	}
	pthread_mutex_destroy(&arg->death_signal);
	if (arg->fork)
		free(arg->fork);
	if (arg)
		free(arg);
	if (thread)
		free(thread);
	if (philo)
		free(philo);

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
	death_checker(philo);
	end_philos(philo, thread, arg);
	return (0);
}
