/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:45:51 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/07 01:57:09 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	else
		return (0);
}

int	checkargv(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
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
	data.start = timestamp();
	pthread_mutex_init(&data.death, NULL);
	pthread_mutex_init(&data.printing, NULL);
	pthread_mutex_init(&data.eating, NULL);
	return (data);
}

int	main(int argc, char **argv)
{
	t_info	data;
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Wrong arguments number");
		return (0);
	}
	while (argv[i])
	{
		if (!checkargv(argv[i]))
		{
			printf("Not a valid number: %s\n", argv[i]);
			return (0);
		}
		i++;
	}
	data = initdata(argv);
	threadbirth(&data);
}