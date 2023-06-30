#include "philo.h"

void	threadbirth(t_info *data)
{
	int	i;
	int	*id;

	i = 0;
	while (i < data->nop)
	{
		pthread_create(id[i], NULLL, void *philolife(void *arg), philo)
		i++;
	}
}
t_info	*parse(char **argv)
{
	t_info	data;

	data.nop = ft_atoi(argv[1]);
	data.ttd = ft_atoi(argv[2]);
	data.tte = ft_atoi(argv[3]);
	data.tts = ft_atoi(argv[4]);
	data.notepme = ft_atoi(argv[5]);
	return (&data);
}

int	main(int argc, char **argv)
{
	t_info	*data;

	if (argc < 6 || argc > 6)
	{
		printf("Wrong arguments number.");
		return (0);
	}
	data = parse(argv);
}