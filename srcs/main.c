#include "philo.h"

t_data	g_p = {};

void	philo_eat(t_philo *p)
{
	int64_t	time;
	int64_t	time_lag;

	grab_forks(p);
	pthread_mutex_lock(&g_p.print_mutex);
	time = get_time();
	if (is_dead(time))
	{
		pthread_mutex_unlock(&g_p.print_mutex);
		return ;
	}
	printf(GREEN"%lld %d has taken a fork\n"END, time, p->id);
	printf(GREEN"%lld %d has taken a fork\n"END, time, p->id);
	time_lag = time - p->last_eat_time;
	if (time_lag > g_p.main[TD])
	{
		g_p.dead_flg = true;
#ifdef DEBUG
		printf(RED"%lld %d has died [%lld]\n"END, time, p->id, time_lag);
#else
		printf(RED"%lld %d has died\n"END, time, p->id);
#endif
		pthread_mutex_unlock(&g_p.print_mutex);
		return ;
	}
	else
	{
#ifdef DEBUG
		printf("[%lld] "END, time_lag);
#endif
		printf(BLUE"%lld %d is eating\n"END, time, p->id);
		p->last_eat_time = time;
		if (g_p.main[EC] != -1 && ++p->eat_count > g_p.main[EC])
			g_p.dead_flg = true;
		pthread_mutex_unlock(&g_p.print_mutex);
		ft_sleep(g_p.main[TE]);
		drop_forks(p);
	}
}

void	philo_action(t_philo *p, char *msg_fmt, int sleep_time)
{
	int64_t	time;

	pthread_mutex_lock(&g_p.print_mutex);
	time = get_time();
	if (is_dead(time))
	{
		pthread_mutex_unlock(&g_p.print_mutex);
		return ;
	}
#ifdef DEBUG
	printf("[%lld] ", time - p->last_eat_time);
#endif
	printf(msg_fmt, time, p->id);
	pthread_mutex_unlock(&g_p.print_mutex);
	ft_sleep(sleep_time);
}

void	*philosopher(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	p->last_eat_time = get_time();
	ft_sleep(p->think_time);
	while (g_p.dead_flg == false)
	{
		philo_eat(p);
		philo_action(p, YELLOW"%lld %d is sleeping\n"END, g_p.main[TS]);
		if (g_p.main[PN] % 2 == 0)
			philo_action(p, MAGENTA"%lld %d is thinking\n"END, 0);
		else
			philo_action(p, MAGENTA"%lld %d is thinking\n"END, 20);
	}
	return (NULL);
}

int	loop_data(void)
{
	int	i;

	if (g_p.main[PN] == 1)
	{
		usleep(g_p.main[TD] * 1000);
		printf(RED"%lld %d has died\n"END, get_time(), 1);
		pthread_mutex_destroy(&g_p.forks[1]);
		return (0);
	}
	i = 0;
	while (++i <= g_p.main[PN])
		pthread_create(&g_p.threads[i], NULL, philosopher, &g_p.philos[i]);
	i = 0;
	while (++i <= g_p.main[PN])
		pthread_join(g_p.threads[i], NULL);
	i = 0;
	while (++i < g_p.main[PN])
		pthread_detach(g_p.threads[i]), pthread_mutex_destroy(&g_p.forks[i]);
	pthread_mutex_destroy(&g_p.print_mutex);
	return (0);
}

int	main(int ac, char **av)
{
	if (check_args_and_store(ac, av))
		return (1);
	return (loop_data());
}
