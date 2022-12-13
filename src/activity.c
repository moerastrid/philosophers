/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   activity.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 14:55:42 by ageels        #+#    #+#                 */
/*   Updated: 2022/12/13 17:59:09 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	isalive(t_philo_info *phinfo)
{
	bool	living;

	usleep(20);
	pthread_mutex_lock(&phinfo->ego);
	living = phinfo->alive;
	pthread_mutex_unlock(&phinfo->ego);
	return (living);
}

static int	phleep(t_philo_info *phinfo)
{
	print_wrap(phinfo->gi, "is sleeping", phinfo);
	if (my_sleep(phinfo->gi->time_to_sleep, phinfo))
		return (1);
	return (0);
}

static int	pheat(t_philo_info *phinfo)
{
	long int	time;

	time = get_time(*phinfo->gi);
	pthread_mutex_lock(&phinfo->ego);
	phinfo->time_last_meal = time;
	pthread_mutex_unlock(&phinfo->ego);
	if (isalive(phinfo) == false)
	{
		put_down_phorks(phinfo);
		return (1);
	}
	print_wrap(phinfo->gi, "is eating", phinfo);
	if (my_sleep(phinfo->gi->time_to_eat, phinfo))
	{
		put_down_phorks(phinfo);
		return (1);
	}
	put_down_phorks(phinfo);
	pthread_mutex_lock(&phinfo->ego);
	phinfo->bites += 1;
	pthread_mutex_unlock(&phinfo->ego);
	return (0);
}

void	get_ready(t_philo_info *phinfo)
{
	bool		ready;
	long int	current_time_ms;

	ready = false;
	while (1)
	{
		usleep(50);
		pthread_mutex_lock(&phinfo->gi->printing);
		ready = phinfo->gi->ready;
		pthread_mutex_unlock(&phinfo->gi->printing);
		if (ready == true)
			break ;
	}
	current_time_ms = get_time(*phinfo->gi);
	if (phinfo->id % 2 == 1)
	{
		while (current_time_ms < (phinfo->gi->time_to_eat * 0.8))
		{
			current_time_ms = get_time(*(phinfo->gi));
			if (isalive(phinfo) != true)
				break ;
		}
	}
}

void	*activity(void *arg)
{
	t_philo_info	*phinfo;

	phinfo = (t_philo_info *)arg;
	get_ready(phinfo);
	//if (phinfo->id % 2 == 1)
	//	my_sleep(phinfo->gi->time_to_eat * 0.8, phinfo);
	if (isalive(phinfo))
		print_wrap(phinfo->gi, "is thinking", phinfo);
	else
		return (NULL);
	while (1)
	{
		if (take_phorks(phinfo) == false)
			break ;
		if (pheat(phinfo))
			break ;
		if (phleep(phinfo))
			break ;
		if (isalive(phinfo) == false)
			break ;
		print_wrap(phinfo->gi, "is thinking", phinfo);
		if (isalive(phinfo) == false)
			break ;
		usleep(50);
	}
	return (NULL);
}
