/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 14:17:00 by dyeboa        #+#    #+#                 */
/*   Updated: 2024/06/03 18:15:09 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <stdlib.h>
#include <unistd.h>
#include <sys/errno.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>

typedef struct s_arg
{
	int				*fork;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_signal;
	pthread_mutex_t	eat_count_lock;
	pthread_mutex_t	create;
	int				created;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	size_t			time_start;
	int				eat_count;
	int				finish;
}	t_arg;

typedef struct s_philo
{
	pthread_mutex_t	is_finish;
	int				finished;
	int				forkright;
	int				forkleft;
	size_t			time_last_ate;
	int				eat_counter;
	int				philo_num;
	t_arg			*arg;
}	t_philo;

int		check_input(int argc, char **argv);
int		init_struct(t_arg *arg, int argc, char **argv);
t_philo	*init_philo(t_arg *arg, char **argv);
size_t	get_time_micro(void);
int		create_threads(pthread_t *thread, t_arg *arg, t_philo *philo);
void	*philo_routine(void *s);
int		sleep_philo(t_philo *philo);
int		think_philo(t_philo *philo);
void	pickup_forks(t_philo *philo);
int		eat_philo(t_philo *philo);
int		ft_atoi(const char *str);
void	print_all(t_philo *philo);
void	death_checker(t_philo *philo);
void	check_death(t_philo *philo);
void	mysleep(size_t time);
int		philostatus(t_philo *philo, char *routine);
int		init_mutex(t_arg *arg);
void	eat_count(t_philo *philo);
void	end_philos(t_philo *philo, pthread_t *thread, t_arg *arg);
void	philo_check_death(t_philo *philo);
int		thread_creation_check(t_philo *philo);

#endif