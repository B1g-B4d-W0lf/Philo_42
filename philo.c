#include "philo.h"

int	isitdead(t_philo *philo)
{
	t_info	*data;

	data = philo->data;
	if (philo->last_eat > data->ttd)
		philo->dead = 1;
	return(philo->dead);
}

void	philoeat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_l));
	status(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->fork_r));
	status(philo, "has taken a fork");
	status(philo, "is eating");
	pthread_mutex_unlock(&(philo->fork_l));
	pthread_mutex_unlock(&(philo->fork_r));
}

void	sleepnthink(t_philo *philo, long long tts)
{
	long long		start;

	start = timestamp;
	while(timestamp - start <= tts)
		if(isitdead(philo) == 1)
			return;
}

void	*philolife(void *phi)
{
	t_philo	*philo;
	t_info	*data;

	philo = (t_philo *)phi;
	data = philo->data;
	while (!isitdead(philo))
	{
		philoeat(philo);
		sleepnthink(philo, data->tts);
	}
	if (isitdead(philo))
		status(philo, "is dead");
	return (NULL);
}

void	placeforks(t_info *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nop)
	{
		pthread_mutex_init(&philo[i].fork_l, NULL);
		i++;
	}
	i = 0;
	while (i < data->nop - 1)
	{
		philo[i].fork_r = philo[i + 1].fork_l;
		i++;
	}
	if (data->nop > 1)
		philo[i].fork_r = philo[0].fork_l;
}

void	threadbirth(t_info *data)
{
	int	i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof (t_philo) * data->nop + 1);
	data->start = timestamp();

	while (i < data->nop)
	{
		philo[i].id = i + 1;
		philo[i].last_eat = data->start;
		philo[i].mc = 0;
		philo[i].dead = 0;
		philo[i].data = data;
		i++;
	}
	i = 0;	
		placeforks(data, philo);
	while (i < data->nop)
	{
		pthread_create(&philo[i].t_id, NULL, philolife, &(philo[i]));
		i++;
	}
	free(philo);
}
