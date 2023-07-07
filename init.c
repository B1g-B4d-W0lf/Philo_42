/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 23:16:43 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/08 00:34:10 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	data.start = timestamp();
	pthread_mutex_init(&data.death, NULL);
	pthread_mutex_init(&data.printing, NULL);
	pthread_mutex_init(&data.eating, NULL);
	return (data);
}

t_philo	initphilo(t_philo philo, int i, t_info *data)
{
	philo.id = i + 1;
	philo.last_eat = data->start;
	philo.mc = 0;
	philo.data = data;
	return (philo);
}
