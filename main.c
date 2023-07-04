#include "philo.h"

t_info	*parse(char **argv)
{
	t_info	data;

	data.nop = ft_atoi(argv[1]);
	data.ttd = ft_atoi(argv[2]);
	data.tte = ft_atoi(argv[3]);
	data.tts = ft_atoi(argv[4]);
	if (argv[5])
		data.notepme = ft_atoi(argv[5]);
	else
		data.notepme = -1;
	return (&data);
}

int	main(int argc, char **argv)
{
	t_info	*data;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong arguments number.");
		return (0);
	}
	data = parse(argv);
	threadbirth(data);
}