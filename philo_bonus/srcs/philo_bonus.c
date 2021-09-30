#include "philo_bonus.h"
#define CHILD 0

static void	ft_sleep(int64_t msec)
{
	int64_t	now;

	now = get_time();
	while (get_time() - now < msec)
	{
		catch_error(usleep(900), "usleep");
	}
}

static void	is_dead(int64_t time)
{
	int64_t	time_lag;
	int		i;

	if (g_p.dead_flg == true)
	{
		philo_exit();
	}
	i = 0;
	while (++i <= g_p.main[PN])
	{
		time_lag = time - g_p.philos[i].last_eat_time;
		if (g_p.philos[i].last_eat_time != 0 && time_lag > g_p.main[TD])
		{
			printf(RED"%lld %d has died\n"END, time, g_p.philos[i].id);
			g_p.dead_flg = true;
			philo_exit();
		}
	}
}

static void	philo_act(t_philo *p, char *msg_fmt, int sleep_time, void \
(*f)(t_philo *, int64_t))
{
	int64_t	time;

	sem_wait(g_p.print_mutex);
	time = get_time();
	is_dead(time);
	f(p, time);
	printf(msg_fmt, time, p->id);
	sem_post(g_p.print_mutex);
	ft_sleep(sleep_time);
}

static void	philosopher(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	sem_wait(g_p.print_mutex);
	if (g_p.dead_flg == true)
	{
		exit(0);
	}
	p->last_eat_time = get_time();
	sem_post(g_p.print_mutex);
	ft_sleep(p->first_think_time);
	while (1)
	{
		philo_act(p, GREEN"%lld %d has taken a fork\n"END, 0, grab_fork);
		philo_act(p, GREEN"%lld %d has taken a fork\n"END, 0, grab_fork);
		philo_act(p, BLUE"%lld %d is eating\n"END, g_p.main[TE], eat);
		drop_forks();
		philo_act(p, YELLOW"%lld %d is sleeping\n"END, g_p.main[TS], ft_void);
		philo_act(p, MAGENTA"%lld %d is thinking\n"END, p->think_time, ft_void);
	}
	exit(0);
}

void	loop_data(void)
{
	int	i;

	if (g_p.main[PN] == 1)
	{
		ft_sleep(g_p.main[TD]);
		printf(RED"%lld %d has died\n"END, get_time(), 1);
		sem_unlink("/print_mutex");
		sem_unlink("/forks");
		sem_unlink("/dead");
		exit(0);
	}
	i = 0;
	while (++i <= g_p.main[PN])
	{
		g_p.process[i] = ft_fork();
		if (g_p.process[i] == CHILD)
		{
			philosopher(&g_p.philos[i]);
		}
	}
	sem_wait(g_p.dead);
	kill_all();
	sem_unlink("/print_mutex");
	sem_unlink("/forks");
	sem_unlink("/dead");
}
