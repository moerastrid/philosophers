/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phorks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 14:51:28 by ageels        #+#    #+#                 */
/*   Updated: 2022/12/01 22:00:15 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	next_id(t_philo_info *phinfo)
{
	int	next_id;

	next_id = phinfo->id + 1;
	if (next_id == phinfo->gi->amount_philo)
		next_id = 0;
	return (next_id);
}

static void	take_right_phork(t_philo_info *phinfo)
{
	pthread_mutex_lock(&phinfo->gi->phorks[next_id(phinfo)]);
	if (isalive(phinfo) == true)
		print_wrap(phinfo->gi, "has taken a fork", phinfo);
	else
		pthread_mutex_unlock(&phinfo->gi->phorks[phinfo->id]);
}

static void	take_left_phork(t_philo_info *phinfo)
{
	pthread_mutex_lock(&phinfo->gi->phorks[phinfo->id]);
	if (isalive(phinfo) == true)
		print_wrap(phinfo->gi, "has taken a fork", phinfo);
	else
		pthread_mutex_unlock(&phinfo->gi->phorks[phinfo->id]);
}

void	take_phorks(t_philo_info *phinfo)
{
	if (phinfo->id % 2 == 1)
	{
		usleep(150);
		take_left_phork(phinfo);
	}
	take_right_phork(phinfo);
	if (phinfo->id % 2 == 0)
		take_left_phork(phinfo);
}

void	put_down_phorks(t_philo_info *phinfo)
{
	pthread_mutex_unlock(&phinfo->gi->phorks[phinfo->id]);
	pthread_mutex_unlock(&phinfo->gi->phorks[next_id(phinfo)]);
}
