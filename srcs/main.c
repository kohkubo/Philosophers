#include "philo.h"
#include <stdlib.h>
#include <sys/time.h>

t_data	g_p = {};

static int	print_usage(void)
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

static int	check_nums_and_store(char **av, int n)
{
	int	i;

	i = 1;
	errno = 0;
	while (i < n)
	{
		if (!is_num_string(av[i]))
			return (ft_error_msg("Invalid arguments: not a number"));
		g_p.main[i - 1] = ft_atoi(av[i]);
		if (g_p.main[i - 1] < 1)
			return (ft_error_msg("Invalid arguments: invalid time"));
		i++;
	}
	if (errno)
		return (ft_error_msg("Invalid arguments: invalid time"));
	return (0);
}

static int	check_args_and_store(int ac, char **av)
{
	if (ac == 1)
		return (print_usage());
	if (ac < 5)
		return (ft_error_msg("Invalid arguments: too few"));
	else if (ac > 6)
		return (ft_error_msg("Invalid arguments: too many"));
	else
		return (check_nums_and_store(av, ac));
}

static int	loop_data(void)
{
	int	i;

	if (gettimeofday(&g_p.start_time, NULL) == -1)
		return (ft_error_msg("gettimeofday() failed"));
	printf("%d start\n", g_p.start_time.tv_usec);
	set_philos_time(g_p.start_time.tv_usec);
	while (1)
	{
		if (gettimeofday(&g_p.now_time, NULL) == -1)
			return (ft_error_msg("gettimeofday() failed"));
		i = 0;
		while (i < g_p.main[PN])
		{
			int	tmp = g_p.now_time.tv_usec - g_p.philos[i].eat_time;
			if (tmp > g_p.main[TD])
			{
				printf("tmp : %d\n", tmp);
				printf("%d %d died\n", g_p.now_time.tv_usec, i);
				return (1);
			}
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	if (check_args_and_store(ac, av))
		return (1);
	return (loop_data());
}
