/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:44:42 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/08 01:31:33 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	isalive(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->death);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->death);
	return (1);
}

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

int	philoeat(t_philo *philo, long long tte)
{
	long long		start;

	start = timestamp();
	philo->last_eat = start;
	status(philo, "is eating", philo->data);
	if (philo->mc >= 0 && philo->mc < philo->data->notepme)
		philo->mc++;
	while (givediff(timestamp(), start) <= tte)
	{
		if (!isalive(philo))
			break ;
		usleep(10);
	}
	if (philo->mc == philo->data->notepme && philo->mc >= 0)
	{
		philo->data->leavingtable++;
		pthread_mutex_unlock(&(philo->fork_l));
		pthread_mutex_unlock((philo->fork_r));
		return (1);
	}
	pthread_mutex_unlock(&(philo->fork_l));
	pthread_mutex_unlock((philo->fork_r));
	return (0);
}

void	sleepnthink(t_philo *philo, long long tts)
{
	long long		start;

	start = timestamp();
	status(philo, "is sleeping", philo->data);
	while (givediff(timestamp(), start) <= tts)
	{
		if (!isalive(philo))
			return ;
		usleep(10);
	}
	status(philo, "is thinking", philo->data);
}
