/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phorks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 14:51:28 by ageels        #+#    #+#                 */
/*   Updated: 2022/12/13 16:18:52 by ageels        ########   odam.nl         */
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

static int	take_right_phork(t_philo_info *phinfo)
{
	pthread_mutex_lock(&phinfo->gi->phorks[next_id(phinfo)]);
	if (isalive(phinfo) == true)
	{
		print_wrap(phinfo->gi, "has taken a fork", phinfo);
		return (1);
	}
	return (0);
}

static int	take_left_phork(t_philo_info *phinfo)
{
	pthread_mutex_lock(&phinfo->gi->phorks[phinfo->id]);
	if (isalive(phinfo) == true)
	{
		print_wrap(phinfo->gi, "has taken a fork", phinfo);
		return (1);
	}
	return (0);
}

bool	take_phorks(t_philo_info *phinfo)
{
	int	left;
	int	right;

	left = -1;
	right = -1;
	if (phinfo->id % 2 == 1)
	{
		left = take_left_phork(phinfo);
	}
	if (left != 0)
		right = take_right_phork(phinfo);
	if (phinfo->id % 2 == 0 && right != 0)
	{
		left = take_left_phork(phinfo);
	}
	if (left == 1 && right == 1)
		return (true);
	else
	{
		if (left == 0)
			pthread_mutex_unlock(&phinfo->gi->phorks[phinfo->id]);
		if (right == 0)
			pthread_mutex_unlock(&phinfo->gi->phorks[next_id(phinfo)]);
		return (false);
	}
}

void	put_down_phorks(t_philo_info *phinfo)
{
	pthread_mutex_unlock(&phinfo->gi->phorks[phinfo->id]);
	pthread_mutex_unlock(&phinfo->gi->phorks[next_id(phinfo)]);
}
