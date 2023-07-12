/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wfreulon <wfreulon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 01:45:41 by wfreulon          #+#    #+#             */
/*   Updated: 2023/07/12 22:23:21 by wfreulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_info
{
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				notepme;
	int				dead;
	int				leavingtable;
	int				wait;
	long long		start;
	pthread_mutex_t	waiting;
	pthread_mutex_t	leaving;
	pthread_mutex_t	printing;
	pthread_mutex_t	death;
	pthread_mutex_t	eating;
}		t_info;

typedef struct s_philo
{
	int				id;
	long long		last_eat;
	int				mc;
	pthread_t		t_id;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	fork_l;
	t_info			*data;
}		t_philo;

//main.c
int			checkargv(char **str);
int			ft_strlencheck(char *str);

//philo.c
int			itisdead(t_philo *philo, t_info *data, int i);
void		placeforks(t_info *data, t_philo *philo);
int			isitdead(t_philo *philo, t_info *data);
void		threadkill(t_philo	*philo, t_info *data);
void		threadbirth(t_info *data);

//utils.c
long		ft_atoi(char *str);
void		status(t_philo *philo, char *str, t_info *data);
long long	timestamp(void);
long long	givediff(long long i, long long j);
int			ft_isdigit(int c);

//living.c
void		*philolife(void *phi);
int			philoeat(t_philo *philo, long long tte);
void		sleepnthink(t_philo *philo, long long tts);
int			isalive(t_philo *philo);
int			takefork(t_philo *philo);

//init.c
void		ft_usleep(t_philo *philo, long long start, long long ttw);
t_info		initdata(char **argv);
t_philo		initphilo(t_philo philo, int i, t_info *data);

/*
si nombre philo est PAIR
temps le + grand * 2
	si time to eat *2 + time to sleep + 10 >= time to die ILS VIVENT
	sinon ils meurent

si nombre philo est IMPAIR
temps le + grand * 3
	si (time to eat * 3)  + time to sleep + 10 >= time to die ILS VIVENT
	sinon ils meurent

 5 599 200 200 MEURENT
 5 610 200 200 VIVENT
 4 399 200 200 MEURENT
 4 410 200 200 VIVENT
*/
#endif