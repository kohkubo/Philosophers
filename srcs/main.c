#include "philo.h"

t_data	g_p = {};

void	philo_eat(t_philo *p)
{
	int64_t	time;

	pthread_mutex_lock(&(g_p.forks[p->fork_left]));
	pthread_mutex_lock(&g_p.print_mutex);
	time = get_time();
	if (is_dead(time))
	{
		pthread_mutex_unlock(&g_p.print_mutex);
		return ;
	}
	printf(GREEN"%lld %d has taken a fork\n"END, time, p->id);
	pthread_mutex_lock(&(g_p.forks[p->fork_right]));
	time = get_time();
	if (is_dead(time))
	{
		pthread_mutex_unlock(&g_p.print_mutex);
		return ;
	}
	printf(GREEN"%lld %d has taken a fork\n"END, time, p->id);
	time = get_time();
	if (is_dead(time))
	{
		pthread_mutex_unlock(&g_p.print_mutex);
		return ;
	}
	printf(BLUE"[%lld] %lld %d is eating\n"END, time - p->last_eat_time, time, p->id);
	pthread_mutex_unlock(&g_p.print_mutex);
	p->last_eat_time = time;
	if (g_p.main[EC] != -1 && ++p->eat_count > g_p.main[EC])
		g_p.dead_flg = true;
	ft_sleep(g_p.main[TE]);
	drop_forks(p);
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
	printf(msg_fmt, time, p->id);
	pthread_mutex_unlock(&g_p.print_mutex);
	ft_sleep(sleep_time);
}

void	philo_action_debug(t_philo *p, char *msg_fmt, int sleep_time)
{
	int64_t	time;

	pthread_mutex_lock(&g_p.print_mutex);
	time = get_time();
	if (is_dead(time))
	{
		pthread_mutex_unlock(&g_p.print_mutex);
		return ;
	}
	printf(msg_fmt, time - p->last_eat_time, time, p->id);
	pthread_mutex_unlock(&g_p.print_mutex);
	ft_sleep(sleep_time);
}

void	*philosopher(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	p->last_eat_time = get_time();
	ft_sleep(p->first_think_time);
	while (g_p.dead_flg == false)
	{
#ifdef DEBUG
		philo_eat(p);
		philo_action_debug(p, YELLOW"[%lld] %lld %d is sleeping\n"END, g_p.main[TS]);
		philo_action_debug(p, MAGENTA"[%lld] %lld %d is thinking\n"END, p->think_time);
#else
		philo_eat(p);
		philo_action(p, YELLOW"%lld %d is sleeping\n"END, g_p.main[TS]);
		philo_action(p, MAGENTA"%lld %d is thinking\n"END, p->think_time);
#endif
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
