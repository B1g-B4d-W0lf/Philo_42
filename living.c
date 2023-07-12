/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:44:42 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/12 21:08:59 by wfreulon         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->data->eating);
	philo->last_eat = start;
	if (philo->mc >= 0 && philo->mc < philo->data->notepme)
		philo->mc++;
	pthread_mutex_unlock(&philo->data->eating);
	status(philo, "is eating", philo->data);
	ft_usleep(philo, start, tte);
	if (philo->mc == philo->data->notepme && philo->mc >= 0)
	{
		pthread_mutex_lock(&philo->data->leaving);
		philo->data->leavingtable++;
		pthread_mutex_unlock(&philo->data->leaving);
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
	ft_usleep(philo, start, tts);
	status(philo, "is thinking", philo->data);
}

void	*philolife(void *phi)
{
	t_philo	*philo;
	t_info	*data;

	philo = (t_philo *)phi;
	data = philo->data;
	if (philo->id % 2)
		ft_usleep(philo, timestamp(), data->tte * 0.25);
	while (isalive(philo))
	{
		if (data->nop % 2)
			ft_usleep(philo, timestamp(), data->ttd * 0.20);
		if (!isalive(philo))
			break ;
		if (!takefork(philo))
			break ;
		if (philoeat(philo, data->tte))
			return (NULL);
		if (!isalive(philo))
			break ;
		sleepnthink(philo, data->tts);
	}
	return (NULL);
}
