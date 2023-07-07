/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:45:04 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/07 01:56:49 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philolife(void *phi)
{
	t_philo	*philo;
	t_info	*data;

	philo = (t_philo *)phi;
	data = philo->data;
	if (philo->id % 2 == 0)
	{
		usleep(data->tte * 0.25);
	}
	while (!isalive(philo))
	{
		philoeat(philo, data->tte);
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

t_philo	initphilo(t_philo philo, int i, t_info *data)
{
	philo.id = i + 1;
	philo.last_eat = data->start;
	philo.mc = 0;
	philo.dead = 0;
	philo.data = data;
	return(philo);
}

void	threadbirth(t_info *data)
{
	int	i;
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
	isitdead(philo, data);
	while (i < data->nop)
	{
		pthread_join(philo[i].t_id, NULL);
		i++;
	}
	undomutex(philo, data);
	free(philo);
}
