#include "philo.h"

int	print_usage(void)
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

void	init_philo(void)
{
	int	i;

	i = 0;
	while (++i <= g_p.main[PN])
	{
		pthread_mutex_init(&(g_p.forks[i]), NULL);
		g_p.philos[i].id = i;
		g_p.philos[i].fork_left = i;
		g_p.philos[i].fork_right = i % g_p.main[PN] + 1;
		if (g_p.main[PN] % 2 == 0)
		{
			if (i % 2 != 0)
				g_p.philos[i].first_think_time = g_p.main[TE];
		}
		else
		{
			if (i % 3 == 0)
				g_p.philos[i].first_think_time = g_p.main[TE];
			else if (i % 3 == 1)
				g_p.philos[i].first_think_time = g_p.main[TE] * 2;
			g_p.philos[i].think_time = 10;
		}
	}
}

int	check_nums_and_store(int ac, char **av)
{
	int	i;

	errno = 0;
	i = 0;
	while (++i < ac)
	{
		if (!is_num_string(av[i]))
			return (ft_error_msg("Invalid arguments: not a number"));
		g_p.main[i] = ft_atoi(av[i]);
		if (g_p.main[i] < 1)
			return (ft_error_msg("Invalid arguments: invalid numbers"));
	}
	if (errno)
		return (ft_error_msg("Invalid arguments: invalid time"));
	if (ac == 5)
		g_p.main[EC] = -1;
	pthread_mutex_init(&(g_p.print_mutex), NULL);
	g_p.dead_flg = false;
	init_philo();
	return (0);
}

int	check_args_and_store(int ac, char **av)
{
	if (ac == 1)
		return (print_usage());
	if (ac < 5)
		return (ft_error_msg("Invalid arguments: too few"));
	else if (ac > 6)
		return (ft_error_msg("Invalid arguments: too many"));
	else
		return (check_nums_and_store(ac, av));
}

int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
