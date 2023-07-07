/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:44:42 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/07 01:59:46 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	isalive(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->dead == 1)
		return (1);
	pthread_mutex_unlock(&philo->data->death);
	return (0);
}

void	isitdead(t_philo *philo, t_info	*data)
{
	int	i;

	i = 0;
	while(i < data->nop)
	{
		long	ms;
	
		if (givediff(timestamp(), philo[i].last_eat) > data->ttd)
		{
			pthread_mutex_lock(&data->death);
			philo[i].dead = 1;
			pthread_mutex_unlock(&data->death);
			pthread_mutex_lock(&data->printing);
			ms = timestamp() - data->start;
			printf("%08ld %d is dead\n", ms, philo[i].id);
			pthread_mutex_unlock(&data->printing);
			return ;
		}
		i++;
		if(i < data->nop)
			i = 0;
	}
}
// 5 599 200 200 MEURENT
// 5 610 200 200 VIVENT
// 4 399 200 200 MEURENT
// 4 410 200 200 VIVENT
void	philoeat(t_philo *philo, long long tte)
{
	long long		start;
	
	pthread_mutex_lock(&philo->data->eating);
	printf("LOCKED by %d\n", philo->id);
	pthread_mutex_lock(&(philo->fork_l));
	status(philo, "has taken a fork", philo->data);
	pthread_mutex_lock((philo->fork_r));
	status(philo, "has taken a fork", philo->data);
	pthread_mutex_unlock(&philo->data->eating);
	printf("UNLOCKED by %d\n", philo->id);
	start = timestamp();
	philo->last_eat = start;
	status(philo, "is eating", philo->data);
	while(givediff(timestamp(), start) <= tte)
		usleep(10);
	pthread_mutex_unlock(&(philo->fork_l));
	pthread_mutex_unlock((philo->fork_r));
}

void	sleepnthink(t_philo *philo, long long tts)
{
	long long		start;

	start = timestamp();
	status(philo, "is sleeping", philo->data);
	while(givediff(timestamp(), start) <= tts)
	{
		if(isalive(philo))
			return;
		usleep(10);
	}
	status(philo, "is thinking", philo->data);
}
