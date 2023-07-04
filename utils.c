#include "philo.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	status(t_philo *philo, char *str)
{
	printf("%d is %s", philo->id, str);
}

int	ft_atoi(char *str)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign = sign * (-1);
		i++;
	}
	while (str[i] <= '0' && str[i] >= '9')
	{
		num = num * 10 + str[i] - 48;
		i++;
	}
	return (num * sign);
}
