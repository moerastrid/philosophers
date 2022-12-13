/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 14:51:22 by ageels        #+#    #+#                 */
/*   Updated: 2022/12/13 15:40:36 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_general_info
{
	int				amount_philo;
	long int		starttime_ms;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				meals;
	bool			meals_set;
	bool			ready;
	pthread_mutex_t	*phorks;
	pthread_mutex_t	printing;
}		t_general_info;

typedef struct s_philo_info
{
	int				id;
	bool			alive;
	int				bites;
	long int		time_last_meal;
	pthread_t		thread;
	pthread_mutex_t	ego;
	t_general_info	*gi;
}		t_philo_info;

//activity
bool		isalive(t_philo_info *phinfo);
void		*activity(void *arg);

// convert
int			convert(int argc, char **argv, t_general_info *gi);

//monitor
int			only_one(t_general_info gi);
void		monitor(t_general_info *gi, t_philo_info *phinfo);

//philosophy
void		philosophy(t_general_info *gi);

//phorks
bool		take_phorks(t_philo_info *phinfo);
void		put_down_phorks(t_philo_info *phinfo);

//time
long int	get_time(t_general_info gi);
void		setup_time(t_general_info *gi);
int			my_sleep(long int duration_ms, t_philo_info *phinfo);

//utils
void		print_wrap(t_general_info *gi, char *s, t_philo_info *phinfo);
int			ft_isdigit(int c);
long int	ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);

#endif