/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:45:04 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/06 03:37:10 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philolife(void *phi)
{
	t_philo	*philo;
	t_info	*data;

	philo = (t_philo *)phi;
	data = philo->data;
	while (!isitdead(philo))
	{
		philoeat(philo);
		sleepnthink(philo, data->tts);
	}
	if (isitdead(philo))
		status(philo, "is dead", philo->data);
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
		philo[i].fork_r = philo[i + 1].fork_l;
		i++;
	}
	if (data->nop > 1)
		philo[i].fork_r = philo[0].fork_l;
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

void	undomutex(t_philo *philo, t_info *data)
{
	int	i;
	
	i = 0;
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->printing);
	while (i < data->nop)
	{
		pthread_mutex_destroy(&philo[i].fork_l);
		i++;
	}	
}

void	threadbirth(t_info *data)
{
	int	i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof (t_philo) * data->nop + 1);
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
	undomutex(philo, data);
	free(philo);
}
