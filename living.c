/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:44:42 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/15 19:44:23 by wfreulon         ###   ########.fr       */
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

int	whilelife(t_philo *philo, t_info *data)
{
	if (data->nop % 2)
		ft_usleep(philo, timestamp(), data->ttd * 0.2);
	if (!isalive(philo))
		return (0);
	if (!takefork(philo))
		return (0);
	if (philoeat(philo, data->tte))
		return (0);
	if (!isalive(philo))
		return (0);
	sleepnthink(philo, data->tts);
	return (1);
}

void	*philolife(void *phi)
{
	t_philo	*philo;
	t_info	*data;

	philo = (t_philo *)phi;
	data = philo->data;
	pthread_mutex_lock(&data->waiting);
	pthread_mutex_unlock(&data->waiting);
	pthread_mutex_lock(&data->eating);
	philo->last_eat = timestamp();
	pthread_mutex_unlock(&data->eating);
	if (philo->id % 2)
		ft_usleep(philo, timestamp(), data->tte * 0.25);
	while (isalive(philo))
	{
		if (!whilelife(philo, data))
			break ;
	}
	return (NULL);
}
