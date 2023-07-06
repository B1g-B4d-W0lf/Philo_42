/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:44:42 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/06 03:44:36 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	isitdead(t_philo *philo)
{
	t_info	*data;

	data = philo->data;
	if (givediff(timestamp(), philo->last_eat) > data->ttd)
		philo->dead = 1;
	else
		philo->dead = 0;

	return(philo->dead);
}

void	philoeat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_l));
	status(philo, "has taken a fork", philo->data);
	pthread_mutex_lock(&(philo->fork_r));
	status(philo, "has taken a fork", philo->data);
	status(philo, "is eating", philo->data);
	pthread_mutex_unlock(&(philo->fork_l));
	pthread_mutex_unlock(&(philo->fork_r));
}

void	sleepnthink(t_philo *philo, long long tts)
{
	long long		start;

	start = timestamp();
	status(philo, "is sleeping", philo->data);
	while(givediff(timestamp(), start) <= tts)
		if(isitdead(philo) == 1)
			return;
	status(philo, "is thining", philo->data);
}
