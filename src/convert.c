/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 14:55:45 by ageels        #+#    #+#                 */
/*   Updated: 2022/12/01 20:58:52 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	convert_argc(t_general_info *gi, int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("usage: philo [number_of_philosophers, time_to_die, ");
		printf("time_to_eat, time_to_sleep, ");
		printf("number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (argc == 6)
		gi->meals_set = 1;
	else
		gi->meals_set = 0;
	return (0);
}

static int	convert_argv(t_general_info *gi, char **argv)
{
	gi->amount_philo = ft_atoi(argv[1]);
	gi->time_to_die = ft_atoi(argv[2]);
	gi->time_to_eat = ft_atoi(argv[3]);
	gi->time_to_sleep = ft_atoi(argv[4]);
	if (gi->meals_set == 1)
		gi->meals = ft_atoi(argv[5]);
	if (gi->amount_philo <= 0 || gi->amount_philo >= 2000)
	{
		printf("No one likes your spaghetti\n");
		return (1);
	}
	if (gi->time_to_die <= 0 || gi->time_to_eat <= 0 || \
	gi->time_to_sleep <= 0)
	{
		printf("Time travel is possible, at least in one direction\n");
		return (1);
	}
	if (gi->meals_set == 1 && gi->meals <= 0)
	{
		printf("Come on, we need to eat!\n");
		return (1);
	}
	return (0);
}

int	convert(int argc, char **argv, t_general_info *gi)
{
	if (convert_argc(gi, argc) || convert_argv(gi, argv))
		return (1);
	setup_time(gi);
	return (0);
}
