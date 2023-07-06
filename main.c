/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:45:51 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/06 03:37:29 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_info	parse(char **argv)
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
	data.start = timestamp();
	pthread_mutex_init(&data.death, NULL);
	pthread_mutex_init(&data.printing, NULL);
	return (data);
}

int	main(int argc, char **argv)
{
	t_info	data;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong arguments number.");
		return (0);
	}
	data = parse(argv);
	threadbirth(&data);
}