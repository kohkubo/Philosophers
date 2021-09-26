#include "philo.h"

t_data	g_p = {};

void print_status(t_philo *p, t_status status)
{
	if (status == EAT)
	{
		grab_forks(p);
		pthread_mutex_lock(&g_p.print_mutex);
		if (g_p.dead_flg == true)
		{
			pthread_mutex_unlock(&g_p.print_mutex);
			return ;
		}
		printf(GREEN"%lld %d has taken a fork\n"END, get_time(), p->id);
		pthread_mutex_unlock(&g_p.print_mutex);
		int64_t time = get_time();
		int64_t time_lag = time - p->last_eat_time;
		if (time_lag >= g_p.main[TD])
		{
			pthread_mutex_lock(&g_p.print_mutex);
			if (g_p.dead_flg == true)
			{
				pthread_mutex_unlock(&g_p.print_mutex);
				return ;
			}
			g_p.dead_flg = true;
			printf(RED"%lld %d has died\n"END, time, p->id);
			// printf(RED"%lld %d has died [%lld]\n"END, time, p->id, time_lag);
			pthread_mutex_unlock(&g_p.print_mutex);
			return ;
		}
		else
		{
			pthread_mutex_lock(&g_p.print_mutex);
			if (g_p.dead_flg == true)
			{
				pthread_mutex_unlock(&g_p.print_mutex);
				return ;
			}
			// printf(BLUE"%lld %d is eating [%lld]\n"END, time, p->id, time_lag);
			printf(BLUE"%lld %d is eating\n"END, time, p->id);
			pthread_mutex_unlock(&g_p.print_mutex);
			p->last_eat_time = time;
			usleep(g_p.main[TE] * 1000);
			drop_forks(p);
		}
	}
	else if (status == SLEEP)
	{
		pthread_mutex_lock(&g_p.print_mutex);
		if (g_p.dead_flg == true)
		{
			pthread_mutex_unlock(&g_p.print_mutex);
			return ;
		}
		printf(YELLOW"%lld %d is sleeping\n"END, get_time(), p->id);
		pthread_mutex_unlock(&g_p.print_mutex);
		usleep(g_p.main[TS] * 1000);
	}
	else if (status == THINK)
	{
		pthread_mutex_lock(&g_p.print_mutex);
		if (g_p.dead_flg == true)
		{
			pthread_mutex_unlock(&g_p.print_mutex);
			return ;
		}
		printf(MAGENTA"%lld %d is thinking\n"END, get_time(), p->id);
		pthread_mutex_unlock(&g_p.print_mutex);
	}
}

void	*philosopher(void *arg)
{
	t_philo *p;

	p = (t_philo *)arg;
	usleep(p->think_time * 1000);
	p->last_eat_time = get_time();
	while (g_p.dead_flg == false)
	{
		print_status(p, EAT);
		print_status(p, SLEEP);
		print_status(p, THINK);
	}
	return (NULL);
}

static int	loop_data(void)
{
	int	i;

	if (gettimeofday(&g_p.start_time, NULL) == -1)
		return (ft_error_msg("gettimeofday() failed"));
	set_philos_time(g_p.start_time.tv_usec);
	if (gettimeofday(&g_p.now_time, NULL) == -1)
		return (ft_error_msg("gettimeofday() failed"));
	i = 0;
	while (++i <= g_p.main[PN])
		pthread_create(&g_p.threads[i], NULL, philosopher, &g_p.philos[i]);
	i = 0;
	while (++i <= g_p.main[PN])
	{
		pthread_join(g_p.threads[i], NULL);
	}
	// pthread_create(&g_p.monitor, NULL, monitor, NULL);
	// pthread_join(g_p.monitor, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	if (check_args_and_store(ac, av))
		return (1);
	return (loop_data());
}
