#include "philo.h"

int	ft_error_msg(const char *emsg)
{
	ft_putendl_fd((char *)emsg, 2);
	return (1);
}

void	set_philos_time(int sec)
{
	int	i;

	i = 0;
	while (i < g_p.main[PN])
	{
		g_p.philos[i].last_eat_time = sec;
		i++;
	}
}

void	debug_print(void)
{
	printf("g_p.main[PN] : %d\n", g_p.main[PN]);
	printf("pn : %d\n", g_p.main[PN]);
	printf("td : %d\n", g_p.main[TD]);
	printf("te : %d\n", g_p.main[TE]);
	printf("ts : %d\n", g_p.main[TS]);
	printf("ec : %d\n", g_p.main[EC]);
	int i = 1;
	while (i <= g_p.main[PN])
	{
		printf("===============\n");
		printf("%d\n", g_p.philos[i].id);
		printf("%d\n", g_p.philos[i].fork_left);
		printf("%d\n", g_p.philos[i].fork_right);
		i++;
	}
}

int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	grab_forks(t_philo *p)
{
	printf("grab_forks p->id : %d\n", p->id);
	pthread_mutex_lock(&(g_p.forks[p->fork_left]));
	pthread_mutex_lock(&(g_p.forks[p->fork_right]));
	printf("grab_forks p->id : %d\n", p->id);
}

void	drop_forks(t_philo *p)
{
	printf("drop_forks p->id : %d\n", p->id);
	pthread_mutex_unlock(&(g_p.forks[p->fork_left]));
	pthread_mutex_unlock(&(g_p.forks[p->fork_right]));
	printf("drop_forks p->id : %d\n", p->id);
}
