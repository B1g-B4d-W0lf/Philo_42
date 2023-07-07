/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:45:41 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/07 01:56:16 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
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
	pthread_mutex_t	eating;
}		t_info;

typedef struct s_philo
{
	int				id;
	long long		last_eat;
	
	int				mc;
	int				dead;
	pthread_t		t_id;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	fork_l;

	t_info			*data;
}		t_philo;

//main.c
void	undomutex(t_philo *philo, t_info *data);

//philo.c
void		threadbirth(t_info *data);

//utils.c
int			ft_atoi(char *str);
void		status(t_philo *philo, char *str, t_info *data);
long long	timestamp(void);
long long	givediff(long long i, long long j);

//living.c
void		isitdead(t_philo *philo, t_info *data);
void		philoeat(t_philo *philo, long long tte);
void		sleepnthink(t_philo *philo, long long tts);
int			isalive(t_philo *philo);


#endif