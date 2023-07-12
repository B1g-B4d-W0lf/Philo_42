/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   livingutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 00:13:37 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/13 00:50:49 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	takefork(t_philo *philo)
{
	if (philo->data->nop == 1)
	{
		status(philo, "has taken a fork", philo->data);
		return (0);
	}
	if (philo->id % 2)
	{
		pthread_mutex_lock(&(philo->fork_l));
		status(philo, "has taken a fork", philo->data);
		pthread_mutex_lock((philo->fork_r));
		status(philo, "has taken a fork", philo->data);
	}
	else
	{
		pthread_mutex_lock((philo->fork_r));
		status(philo, "has taken a fork", philo->data);
		pthread_mutex_lock(&(philo->fork_l));
		status(philo, "has taken a fork", philo->data);
	}
	return (1);
}

void	ft_usleep(t_philo *philo, long long start, long long ttw)
{
	while (givediff(timestamp(), start) <= ttw)
	{
		if (!isalive(philo))
			break ;
		usleep(10);
	}
	return ;
}
