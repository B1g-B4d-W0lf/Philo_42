/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:45:04 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/12 23:08:24 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	itisdead(t_philo *philo, t_info *data, int i)
{
	long	ms;

	data->dead = 1;
	pthread_mutex_unlock(&data->death);
	pthread_mutex_lock(&data->printing);
	ms = timestamp() - data->start;
	printf("%08ld %d is dead\n", ms, philo[i].id);
	pthread_mutex_unlock(&data->printing);
	return (1);
}

int	isitdead(t_philo *philo, t_info	*data)
{
	int				i;
	long long		last_eat;

	i = 0;
	while (i < data->nop)
	{
		pthread_mutex_lock(&data->eating);
		last_eat = givediff(timestamp(), philo[i].last_eat);
		pthread_mutex_unlock(&data->eating);
		pthread_mutex_lock(&data->death);
		if (last_eat > data->ttd)
			return (itisdead(philo, data, i));
		pthread_mutex_unlock(&data->death);
		pthread_mutex_lock(&philo->data->leaving);
		if (data->leavingtable == data->nop)
			return (pthread_mutex_unlock(&philo->data->leaving), 1);
		pthread_mutex_unlock(&philo->data->leaving);
		i++;
		if (i == data->nop)
			i = 0;
	}
	return (0);
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
