/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 15:37:20 by ageels        #+#    #+#                 */
/*   Updated: 2022/12/13 18:14:24 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	setup_time(t_general_info *gi)
{
	struct timeval	stime;

	gettimeofday(&stime, NULL);
	gi->starttime_ms = (stime.tv_sec * 1000) + stime.tv_usec * 0.001;
}

long int	get_time(t_general_info gi)
{
	struct timeval	ctime;
	long int		ctime_ms;

	gettimeofday(&ctime, NULL);
	ctime_ms = (ctime.tv_sec * 1000) + ctime.tv_usec * 0.001;
	return (ctime_ms - gi.starttime_ms);
}

int	my_sleep(long int duration_ms, t_philo_info *phinfo)
{
	long int	starttime_ms;
	long int	current_time_ms;

	starttime_ms = get_time(*phinfo->gi);
	current_time_ms = starttime_ms;
	while (current_time_ms - starttime_ms < duration_ms)
	{
		usleep(150);
		current_time_ms = get_time(*(phinfo->gi));
		if (isalive(phinfo) != true)
			return (1);
	}
	return (0);
}
