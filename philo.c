/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:45:04 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/08 01:32:20 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philolife(void *phi)
{
	t_philo	*philo;
	t_info	*data;

	philo = (t_philo *)phi;
	data = philo->data;
	if (philo->id % 2)
		usleep(5000);
	while (isalive(philo))
	{
		if (data->nop % 2)
			usleep(20000);
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

void	placeforks(t_info *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nop)
	{
		pthread_mutex_init(&philo[i].fork_l, NULL);
		i++;
	}
	i = 0;
	while (i < data->nop - 1)
	{
		philo[i].fork_r = &philo[i + 1].fork_l;
		i++;
	}
	if (data->nop > 1)
	{
		philo[i].fork_r = &philo[0].fork_l;
	}
}

void	isitdead(t_philo *philo, t_info	*data)
{
	int		i;
	long	ms;

	i = 0;
	while (i < data->nop)
	{
		if (givediff(timestamp(), philo[i].last_eat) > data->ttd)
		{
			pthread_mutex_lock(&data->death);
			data->dead = 1;
			pthread_mutex_unlock(&data->death);
			pthread_mutex_lock(&data->printing);
			ms = timestamp() - data->start;
			printf("%08ld %d is dead\n", ms, philo[i].id);
			pthread_mutex_unlock(&data->printing);
			return ;
		}
		else if (data->leavingtable == data->nop)
			return ;
		i++;
		if (i == data->nop)
			i = 0;
	}
}

void	threadkill(t_philo	*philo, t_info *data)
{
	int	i;

	i = 0;
	isitdead(philo, data);
	while (i < data->nop)
	{
		pthread_join(philo[i].t_id, NULL);
		i++;
	}
	free(philo);
}

void	threadbirth(t_info *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof (t_philo) * data->nop);
	if (!philo)
		return ;
	while (i < data->nop)
	{
		philo[i] = initphilo(philo[i], i, data);
		i++;
	}
	i = 0;
	placeforks(data, philo);
	while (i < data->nop)
	{
		pthread_create(&philo[i].t_id, NULL, philolife, &(philo[i]));
		i++;
	}
	threadkill(philo, data);
}
