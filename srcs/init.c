#include "philo.h"

int	print_usage(void)
{
	ft_putstr_fd("\
Usage: ./philo PN TD TE TS [EC]\n\n\
\
	PN = number of philosophers\n\
	TD = time to die\n\
	TE = time to eat\n\
	TS = time to sleep\n\
	EC = number of times each philosopher must eat\n"\
, 1);
	return (0);
}

int	check_nums_and_store(int ac, char **av)
{
	int	i;

	errno = 0;
	g_p.dead_flg = false;
	pthread_mutex_init(&(g_p.print_mutex), NULL);
	i = 0;
	while (++i < ac)
	{
		if (!is_num_string(av[i]))
			return (ft_error_msg("Invalid arguments: not a number"));
		g_p.main[i] = ft_atoi(av[i]);
		pthread_mutex_init(&(g_p.forks[i]), NULL);
		if (g_p.main[i] < 1)
			return (ft_error_msg("Invalid arguments: invalid time"));
	}
	i = 0;
	while (++i <= g_p.main[PN])
	{
		g_p.philos[i].id = i;
		g_p.philos[i].fork_left = i;
		g_p.philos[i].fork_right = i % g_p.main[PN] + 1;
		g_p.philos[i].eat_count = 0;
		g_p.philos[i].last_eat_time = 0;
	}
	if (errno)
		return (ft_error_msg("Invalid arguments: invalid time"));
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
