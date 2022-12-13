/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 18:48:56 by ageels        #+#    #+#                 */
/*   Updated: 2022/12/13 17:27:18 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	only_one(t_general_info gi)
{
	if (gi.amount_philo == 1)
	{
		printf("%ld\t1 has taken a fork\n", get_time(gi));
		usleep(gi.time_to_die * 1000);
		printf("%ld\t1 died\n", get_time(gi));
		return (1);
	}
	return (0);
}

static void	kill_them_all(t_general_info *gi, t_philo_info *phinfo)
{
	int	i;

	i = 0;
	while (i < gi->amount_philo)
	{
		pthread_mutex_lock(&phinfo[i].ego);
		phinfo[i].alive = false;
		pthread_mutex_unlock(&phinfo[i].ego);
		i++;
	}
}

static int	he_dead(t_general_info *gi, t_philo_info *phinfo)
{
	long int	current_time;
	long int	time_last_meal;

	current_time = get_time(*gi);
	pthread_mutex_lock(&phinfo->ego);
	time_last_meal = phinfo->time_last_meal;
	pthread_mutex_unlock(&phinfo->ego);
	if (current_time - time_last_meal > gi->time_to_die)
	{
		return (phinfo->id + 1);
	}
	return (0);
}

static bool	he_full(t_general_info *gi, t_philo_info *phinfo)
{
	int	bites;

	pthread_mutex_lock(&phinfo->ego);
	bites = phinfo->bites;
	pthread_mutex_unlock(&phinfo->ego);
	if (bites >= gi->meals)
		return (1);
	return (0);
}

void	monitor(t_general_info *gi, t_philo_info *phinfo)
{
	int	i;
	int	full;
	int	deadphilo_id;

	deadphilo_id = 0;
	i = 0;
	full = 0;
	while (1)
	{
		if (i >= gi->amount_philo)
		{
			usleep(20);
			i = 0;
			full = 0;
		}
		if (gi->meals_set)
			full += he_full(gi, &phinfo[i]);
		deadphilo_id = he_dead(gi, &phinfo[i]);
		if ((full == gi->amount_philo) || deadphilo_id)
		{
			kill_them_all(gi, phinfo);
			if (deadphilo_id != 0)
			{
				pthread_mutex_lock(&gi->printing);
				printf("%ld\t%d %s\n", get_time(*gi), deadphilo_id, "died");
				pthread_mutex_unlock(&gi->printing);
			}
			break ;
		}
		i++;
	}
}
