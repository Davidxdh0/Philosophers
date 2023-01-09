/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/05 20:08:30 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/01/09 15:28:31 by dyeboa        ########   odam.nl         */
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
			if (!ft_isdigit(argv[i][j]))
			{
				printf("fout %c [i = %d][j = %d",argv[i][j], i, j);
				return(1);
			}
			j++;
		}
		i++;
	}
	printf("input\n");
	return (0);
}

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
	if (arg->philo_num < 1 || arg->time_to_die < 1 || arg->time_to_eat < 1 \
		|| arg->time_to_sleep < 1 || arg->number_must_eat < 0)
		return (1);
	printf("init struct num = %d die = %d, eat = %d sleep = %d start = %zu \n", arg->philo_num, arg->time_to_die, arg->time_to_eat, arg->time_to_sleep, arg->time_start);
	printf("init struct\n");
	return (0);
}

size_t	get_time_micro()
{
	struct timeval time ;
	// {
    //  time_t       tv_sec;   /* seconds since Jan. 1, 1970 */
    // 	suseconds_t  tv_usec;  /* MICROseconds */
    //  };
	gettimeofday(&time, NULL);
	return(time.tv_sec * 1000000 + time.tv_usec);
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
		//printf("%zu\n", philo[i].time_last_ate);
		//philo[i].tid = tid[i];
		philo[i].eat_count = 0;
		philo[i].arg = arg;
		i++;
	}
	printf("init philo\n");
	return (philo);
}
void sleep_philo(t_philo *philo)
{
	printf("%d is sleeping %d microseconds\n", philo->philo_num, philo->arg->time_to_sleep);
	usleep(philo->arg->time_to_sleep * 1000);
}

void think_philo(t_philo *philo)
{
	printf("%d is thinking\n", philo->philo_num);	
}

void eat_philo(t_philo *philo)
{
	printf("%d is eating\n", philo->philo_num);	
}

void *philo_routine(void *s)
{
	t_philo *philo;

	philo = (t_philo *)(s);
	//printf("routine num = %d die = %d, eat = %d sleep = %d \n", philo->philo_num,  philo->arg->time_to_die,  philo->arg->time_to_eat,  philo->arg->time_to_sleep);
	while(1)
	{
		// mutexen
		// eat()
		sleep_philo(philo);
		think_philo(philo);
	}
	return NULL;
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
		usleep(20);
		i++;
	}
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
		return(1);
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
	printf("dood of free'en");
	//
	

	
	//Begin eten
	return (0);
}
