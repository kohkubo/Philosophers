#include "philo_bonus.h"

static void	print_usage_exit(void)
{
	printf("\
Usage: ./philo PN TD TE TS [EC]\n\n\
\
	PN = number of philosophers\n\
	TD = time to die\n\
	TE = time to eat\n\
	TS = time to sleep\n\
	EC = number of times each philosopher must eat\n");
	exit(0);
}

static void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (++i <= data->main[PN])
	{
		data->philos[i].id = i;
		data->philos[i].dead_flg = &data->dead_flg;
		data->philos[i].last_eat_time = data->last_eat_time;
		data->philos[i].forks = data->forks;
		data->philos[i].mutex = data->mutex;
		data->philos[i].dead = data->dead;
		data->philos[i].main[PN] = data->main[PN];
		data->philos[i].main[TD] = data->main[TD];
		data->philos[i].main[TE] = data->main[TE];
		data->philos[i].main[TS] = data->main[TS];
		data->philos[i].main[EC] = data->main[EC];
		data->philos[i].left_philo = i;
		data->philos[i].right_philo = i % data->main[PN] + 1;
		store_sleeptime(data, i);
	}
}

static void	check_nums_and_store(t_data *data, int ac, char **av)
{
	int	i;

	errno = 0;
	i = 0;
	while (++i < ac)
	{
		if (!is_num_string(av[i]))
			ft_error_exit("Invalid arguments: not a number");
		data->main[i] = ft_atoi(av[i]);
		if (data->main[i] < 1)
			ft_error_exit("Invalid arguments: invalid numbers");
	}
	if (errno)
		ft_error_exit("Invalid arguments: invalid time");
	if (PN_MAX < data->main[PN])
		ft_error_exit("Invalid arguments: too many philosophers");
	if (ac == 5)
		data->main[EC] = -1;
	errno = 0;
	data->mutex = ft_sem_open("/mutex", 1);
	data->forks = ft_sem_open("/forks", data->main[PN]);
	data->dead = ft_sem_open("/dead", 0);
	data->dead_flg = false;
}

static void	check_ac(int ac)
{
	if (ac == 1)
		print_usage_exit();
	if (ac < 5)
		ft_error_exit("Invalid arguments: too few");
	else if (ac > 6)
		ft_error_exit("Invalid arguments: too many");
}

int	main(int ac, char **av)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	check_ac(ac);
	check_nums_and_store(&data, ac, av);
	init_philo(&data);
	loop_data(&data);
	return (0);
}
