/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:45:51 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/11 19:31:23 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checkargv(char **str)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (str[i])
	{
		while (str[i][j])
		{
			if (ft_isdigit(str[i][j]))
				j++;
			else
			{
				printf("Not a valid positive number: %s\n", str[i]);				
				return (0);
			}
		}
		i++;
		j = 0;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	data;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong arguments number\n");
		return (0);
	}
	if (!checkargv(argv))
			return (0);
	data = initdata(argv);
	if (data.nop <= 0 || data.tte < 0 || data.ttd < 0 || 
		data.tts < 0 || data.nop > 250)
	{
		printf("Invalid arguments\n");
		return (0);
	}
	threadbirth(&data);
}
