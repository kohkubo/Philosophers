#include "philo_bonus.h"

t_data	g_p = {};

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

static void	init_philo(void)
{
	int	i;

	i = 0;
	while (++i <= g_p.main[PN])
	{
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

static void	check_nums_and_store(int ac, char **av)
{
	int	i;

	errno = 0;
	i = 0;
	while (++i < ac)
	{
		if (!is_num_string(av[i]))
			ft_error_exit("Invalid arguments: not a number");
		g_p.main[i] = ft_atoi(av[i]);
		if (g_p.main[i] < 1)
			ft_error_exit("Invalid arguments: invalid numbers");
	}
	if (errno)
		ft_error_exit("Invalid arguments: invalid time");
	if (PN_MAX < g_p.main[PN])
		ft_error_exit("Invalid arguments: too many philosophers");
	if (ac == 5)
		g_p.main[EC] = -1;
	g_p.print_mutex = sem_open("/print_mutex", O_CREAT, 0644, 0);
	g_p.forks = sem_open("/forks", O_CREAT, 0644, g_p.main[PN]);
	g_p.dead_flg = false;
	init_philo();
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
	check_ac(ac);
	check_nums_and_store(ac, av);
	loop_data();
	return (0);
}
