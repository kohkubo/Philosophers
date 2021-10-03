#include "philo.h"

static int	print_usage(void)
{
	printf("\
Usage: ./philo PN TD TE TS [EC]\n\n\
\
	PN = number of philosophers\n\
	TD = time to die\n\
	TE = time to eat\n\
	TS = time to sleep\n\
	EC = number of times each philosopher must eat\n");
	return (0);
}

static void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(data->print_mutex), NULL);
	data->dead_flg = false;
	while (++i <= data->main[PN])
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		data->philos[i].id = i;
		data->philos[i].dead_flg = &data->dead_flg;
		data->philos[i].last_eat_time = data->last_eat_time;
		data->philos[i].print_mutex = &data->print_mutex;
		data->philos[i].forks = data->forks;
		data->philos[i].main[PN] = data->main[PN];
		data->philos[i].main[TD] = data->main[TD];
		data->philos[i].main[TE] = data->main[TE];
		data->philos[i].main[TS] = data->main[TS];
		data->philos[i].main[EC] = data->main[EC];
		data->philos[i].fork_left = i;
		data->philos[i].fork_right = i % data->main[PN] + 1;
		if (data->main[PN] % 2 == 0)
		{
			if (i % 2 != 0)
				data->philos[i].first_think_time = data->main[TE];
			// data->philos[i].think_time = 10;
		}
		else
		{
			if (i % 3 == 0)
				data->philos[i].first_think_time = data->main[TE];
			else if (i % 3 == 1)
				data->philos[i].first_think_time = data->main[TE] * 2;
			data->philos[i].think_time = 10;
		}
	}
}

static int	check_nums_and_store(int ac, char **av, t_data *data)
{
	int	i;

	errno = 0;
	i = 0;
	while (++i < ac)
	{
		if (!is_num_string(av[i]))
			return (ft_error_msg("Invalid arguments: not a number"));
		data->main[i] = ft_atoi(av[i]);
		if (data->main[i] < 1)
			return (ft_error_msg("Invalid arguments: invalid numbers"));
	}
	if (errno)
		return (ft_error_msg("Invalid arguments: invalid time"));
	if (PN_MAX < data->main[PN])
		return (ft_error_msg("Invalid arguments: too many philosophers"));
	if (ac == 5)
		data->main[EC] = -1;
	init_philo(data);
	return (0);
}

static int	check_ac(int ac)
{
	if (ac == 1)
		return (print_usage());
	if (ac < 5)
		return (ft_error_msg("Invalid arguments: too few"));
	else if (ac > 6)
		return (ft_error_msg("Invalid arguments: too many"));
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (check_ac(ac))
		return (1);
	if (check_nums_and_store(ac, av, &data))
		return (1);
	return (loop_data(&data));
}
