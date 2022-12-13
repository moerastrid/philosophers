/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 14:14:16 by ageels        #+#    #+#                 */
/*   Updated: 2022/12/13 18:18:04 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_wrap(t_general_info *gi, char *s, t_philo_info *phinfo)
{
	pthread_mutex_lock(&gi->printing);
	printf("%ld\t%d %s\n", get_time(*gi), phinfo->id + 1, s);
	pthread_mutex_unlock(&gi->printing);
}

int	ft_isdigit(int c)
{
	int	i;

	i = 0;
	if (c >= '0' && c <= '9')
		i = 1;
	return (i);
}

long int	ft_atoi(const char *str)
{
	int			i;
	long int	result;
	int			mincounter;

	i = 0;
	result = 0;
	mincounter = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == '\n')
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			mincounter = mincounter * -1;
		i++;
	}
	while (str[i] != '\0' && ft_isdigit(str[i]) == 1)
	{
		result = (result * 10);
		result = (result + (str[i] - '0'));
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (result * mincounter);
}

void	ft_bzero(void *s, size_t n)
{
	char	*stemp;
	size_t	a;

	stemp = (char *)s;
	a = 0;
	while (a != n)
	{
		stemp[a] = '\0';
		a++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*point;

	point = malloc(count * size);
	if (point == NULL)
		return (NULL);
	ft_bzero(point, size * count);
	return (point);
}
