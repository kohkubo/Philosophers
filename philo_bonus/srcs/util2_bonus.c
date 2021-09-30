#include "philo_bonus.h"

void	grab_forks(t_philo *p)
{
	int64_t	time;

	sem_wait(g_p.forks);
	time = get_time();
	is_dead(time, p);
	printf(GREEN"%lld %d has taken a fork\n"END, time, p->id);
	sem_wait(g_p.forks);
	time = get_time();
	is_dead(time, p);
	printf(GREEN"%lld %d has taken a fork\n"END, time, p->id);
}

void	drop_forks(void)
{
	sem_post(g_p.forks);
	sem_post(g_p.forks);
}

void	ft_sleep(int64_t msec)
{
	int64_t	now;

	now = get_time();
	while (get_time() - now < msec)
	{
		usleep(900);
	}
}

void	kill_all(int id)
{
	int		i;

	i = 0;
	while (i < g_p.main[PN])
	{
		if (i != id)
			kill(g_p.process[i], SIGKILL);
		i++;
	}
}

void	is_dead(int64_t time, t_philo *p)
{
	int64_t	time_lag;
	int		i;

	if (g_p.dead_flg == true)
	{
		// sem_wait(g_p.print_mutex);
		printf("a1\n");
		kill_all(p->id);
		exit(0);
	}
	i = 0;
	while (++i <= g_p.main[PN])
	{
		time_lag = time - g_p.philos[i].last_eat_time;
		if (g_p.philos[i].last_eat_time != 0 && time_lag > g_p.main[TD])
		{
			printf(RED"%lld %d has died\n"END, time, g_p.philos[i].id);
			g_p.dead_flg = true;
			// sem_wait(g_p.print_mutex);
			kill_all(p->id);
			printf("a2\n");
			exit(0);
		}
	}
}
