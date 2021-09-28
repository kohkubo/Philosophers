#include "philo_bonus.h"

void	grab_forks(t_philo *p)
{
	int64_t	time;

	sem_wait(g_p.forks);
	time = get_time();
	is_dead(time);
	printf(GREEN"%lld %d has taken a fork\n"END, time, p->id);
	sem_wait(&(g_p.forks[p->fork_right]));
	time = get_time();
	is_dead(time);
	printf(GREEN"%lld %d has taken a fork\n"END, time, p->id);
}

void	drop_forks(t_philo *p)
{
	sem_post(&(g_p.forks[p->fork_left]));
	sem_post(&(g_p.forks[p->fork_right]));
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

void	is_dead(int64_t time)
{
	int64_t	time_lag;
	int		i;

	if (g_p.dead_flg == true)
	{
		sem_post(g_p.print_mutex);
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
			sem_post(g_p.print_mutex);
			exit(0);
		}
	}
}
