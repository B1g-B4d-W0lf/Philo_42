#include "philo.h"


void	philolife(void *phi)
{
	t_philo	philo;

	philo = (t_philo)phi;
	while (philoalive)
	{
		philoeat
			status(philo, "eating");
		philosleep
			status(philo, "sleeping");
		philothink
			status(philo, "thinking");
	}
	philodied
		status(philo, "dead");

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
	i = 1;
	while (i < data->nop)
	{
		philo[i]->fork_r = philo[i + 1]->fork_l;
		i++;
	}
}

void	threadbirth(t_info *data)
{
	int	i;
	t_philo	*philo;

	i = 0;
	data->start = timestamp();
	placeforks(data, philo);
	while (i < data->nop)
	{
		philo[i].id = i + 1;
		philo[i].last_eat = 0;
		philo[i].mc = 0;
		philo[i].data = data;
		pthread_create(&philo[i].t_id, NULL, &philolife, &(philo[i]));
		i++;
	}
}
