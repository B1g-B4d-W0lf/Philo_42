/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:45:32 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/06 03:48:23 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	givediff(long long i, long long j)
{
	long long res;
	res = i - j;
	return(res);
}

long long	timestamp(void)
{
	struct timeval	t;
	long long	timeofday;

	gettimeofday(&t, NULL);
	timeofday =	(t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (timeofday);
}

void	status(t_philo *philo, char *str, t_info *data)
{
	long int	ms;
	
	pthread_mutex_lock(&data->printing);
	ms = timestamp() - data->start;
	printf("%08ld %d %s\n", ms, philo->id, str);
	pthread_mutex_unlock(&data->printing);
}

int	ft_atoi(char *str)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign = sign * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - 48;
		i++;
	}
	return (num * sign);
}
