/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:45:41 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/06 03:36:35 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef	struct	s_info
{
	int				nop;
	int				ttd;
	int 			tte;
	int				tts;
	int				notepme;
	long long		start;
	pthread_mutex_t	printing;
	pthread_mutex_t	death;
}		t_info;

typedef struct s_philo
{
	int				id;
	long long		last_eat;
	int				eating;
	int				mc;
	int				dead;
	pthread_t		t_id;
	pthread_mutex_t	fork_r;
	pthread_mutex_t	fork_l;
	t_info			*data;
}		t_philo;

//philo.c
void		threadbirth(t_info *data);

//utils.c
int			ft_atoi(char *str);
void		status(t_philo *philo, char *str, t_info *data);
long long	timestamp(void);
long long	givediff(long long i, long long j);

//living.c
int			isitdead(t_philo *philo);
void		philoeat(t_philo *philo);
void		sleepnthink(t_philo *philo, long long tts);


#endif