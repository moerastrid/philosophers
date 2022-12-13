/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 14:51:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/12/13 19:12:55 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_general_info	gi;

	if (convert(argc, argv, &gi))
		return (1);
	if (only_one(gi))
		return (0);
	philosophy(&gi);
	return (0);
}
