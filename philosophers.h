/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 14:17:00 by dyeboa        #+#    #+#                 */
/*   Updated: 2023/01/26 14:34:45 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdlib.h>
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
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_must_eat;
	size_t			time_start;
	int				eat_cnt;
	int				finish;
}	t_arg;

typedef struct s_philo
{
	int 		forkright;
	int			forkleft;
	size_t		time_last_ate;
	int			eat_count;
	int			philo_num;
	pthread_t	tid;
	t_arg		*arg;
}	t_philo;

//static int	ft_isspace(int c);
int		check_input(int argc, char **argv);
int 	init_struct(t_arg *arg, int argc, char **argv);
t_philo *init_philo(t_arg *arg, char **argv);
size_t	get_time_micro();
int		create_threads(pthread_t *thread, t_arg *arg, t_philo *philo);
void 	*philo_routine(void *s);
void 	sleep_philo(t_philo *philo);
void 	think_philo(t_philo *philo);
void 	eat_philo(t_philo *philo);
int		ft_atoi(const char *str);
void	print_all(t_philo *philo);
void	death_checker(t_philo *philo, t_arg *arg);
void	check_death(t_philo *philo);
void	mysleep(useconds_t time);
void	philostatus(t_philo *philo, char *routine);
#endif