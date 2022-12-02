/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 14:55:48 by ageels        #+#    #+#                 */
/*   Updated: 2022/12/02 15:07:35 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	init_gmutex(t_general_info *gi)
{
	int	i;

	gi->phorks = ft_calloc(gi->amount_philo, sizeof(pthread_mutex_t));
	if (!gi->phorks)
		return (1);
	i = 0;
	while (i < gi->amount_philo)
	{
		pthread_mutex_init(&(gi->phorks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&gi->printing, NULL);
	return (0);
}

void	init_philos(t_general_info *gi, t_philo_info	*phinfo)
{
	int	i;

	i = 0;
	while (i < gi->amount_philo)
	{
		phinfo[i].id = i;
		phinfo[i].alive = true;
		phinfo[i].bites = 0;
		phinfo[i].gi = gi;
		phinfo[i].time_last_meal = 0;
		pthread_mutex_init(&phinfo[i].ego, NULL);
		i++;
	}
	pthread_mutex_lock(&gi->printing);
	gi->ready = false;
	pthread_mutex_unlock(&gi->printing);
	i = 0;
	while (i < gi->amount_philo)
	{
		pthread_create(&phinfo[i].thread, NULL, &activity, &phinfo[i]);
		i++;
	}
	pthread_mutex_lock(&gi->printing);
	gi->ready = true;
	pthread_mutex_unlock(&gi->printing);
}

void	clean_philos(t_general_info *gi, t_philo_info	*phinfo)
{
	int	i;

	i = 0;
	while (i < gi->amount_philo)
	{
		pthread_join(phinfo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < gi->amount_philo)
	{
		pthread_mutex_destroy(&phinfo[i].ego);
		pthread_mutex_destroy(&gi->phorks[i]);
		i++;
	}
	pthread_mutex_destroy(&gi->printing);
	free(gi->phorks);
	free(phinfo);
}

void	philosophy(t_general_info *gi)
{
	t_philo_info	*phinfo;

	phinfo = ft_calloc(gi->amount_philo, sizeof(t_philo_info));
	if (init_gmutex(gi))
		return ;
	init_philos(gi, phinfo);
	monitor(gi, phinfo);
	clean_philos(gi, phinfo);
}
