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
	int	start;
}		t_info;

typedef struct s_philo
{
	int						id;
	int						last_eat;
	int						eating;
	int						mc;
	pthread_t				t_id;
	pthread_mutex_t			fork_r;
	pthread_mutex_t			fork_l;
	t_info					*data;

}		t_philo;
//philo.c
void	threadbirth(t_info *data);

//utils.c
int		ft_atoi(char *str);
void	status(t_philo *philo, char *str);
long long	timestamp(void);


#endif