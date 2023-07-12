/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 23:16:43 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/12 20:50:05 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_info	initdata(char **argv)
{
	t_info	data;

	data.nop = ft_atoi(argv[1]);
	data.ttd = ft_atoi(argv[2]);
	data.tte = ft_atoi(argv[3]);
	data.tts = ft_atoi(argv[4]);
	if (argv[5])
		data.notepme = ft_atoi(argv[5]);
	else
		data.notepme = -1;
	data.dead = 0;
	data.leavingtable = 0;
	data.start = timestamp();
	pthread_mutex_init(&data.leaving, NULL);
	pthread_mutex_init(&data.death, NULL);
	pthread_mutex_init(&data.printing, NULL);
	pthread_mutex_init(&data.eating, NULL);
	return (data);
}

t_philo	initphilo(t_philo philo, int i, t_info *data)
{
	philo.id = i + 1;
	philo.last_eat = data->start;
	if (data->notepme >= 0)
		philo.mc = 0;
	else
		philo.mc = -1;
	philo.data = data;
	return (philo);
}
