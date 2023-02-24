/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 14:17:00 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/02/24 11:32:39 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <pthread.h>
# include <sys/time.h>

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
int		eat_philo(t_philo *philo);
int		ft_atoi(const char *str);
void	print_all(t_philo *philo);
void	death_checker(t_philo *philo);
void	check_death(t_philo *philo);
void	mysleep(useconds_t time);
int		philostatus(t_philo *philo, char *routine);
int		init_mutex(t_arg *arg);
int		finish(t_philo *philo);
void	eat_count(t_philo *philo);
void	check_fork(t_philo *philo, int fork);
void	drop_fork(t_philo *philo, int fork);
void	end_philos(t_philo *philo, pthread_t *thread, t_arg *arg);
void	philo_check_death(t_philo *philo);
int		thread_creation_check(t_philo *philo);

#endif