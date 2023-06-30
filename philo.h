#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef	struct	s_info
{
	int	nop;
	int	ttd;
	int tte;
	int	tts;
	int	notepme;
}		t_info;

//philo.c

//utils.c
int	ft_atoi(char *str);

#endif