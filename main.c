/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:45:51 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/08 01:29:17 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checkargv(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	data;
	int		i;

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
