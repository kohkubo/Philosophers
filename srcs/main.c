#include "philo.h"

t_data	g_p = {};
#define DEBUG
// ./philo 200 410 200 200 | awk '{print $1}' | tee act | sort -n > exp; diff -u exp act
// ❯ ./philo 4 410 200 200 | awk '{print substr($1, length($1) - 12, 13) " " $2 " " $NF}'

void	ft_sleep(int64_t msec)
{
	int64_t	now;

	now = get_time();
	while (get_time() - now < msec)
	{
		usleep(900);
	}
}

void	philo_eat(t_philo *p)
{
	grab_forks(p);
	pthread_mutex_lock(&g_p.print_mutex);
	if (g_p.dead_flg == true)
	{
		pthread_mutex_unlock(&g_p.print_mutex);
		return ;
	}
	int64_t time = get_time();
	printf(GREEN"%lld %d has taken a fork\n"END, time, p->id);
	printf(GREEN"%lld %d has taken a fork\n"END, time, p->id);
	int64_t time_lag = time - p->last_eat_time;
	if (time_lag >= g_p.main[TD])
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
		printf(BLUE"%lld %d is eating [%lld]\n"END, time, p->id, time_lag);
#else
		printf(BLUE"%lld %d is eating\n"END, time, p->id);
#endif
		pthread_mutex_unlock(&g_p.print_mutex);
		p->last_eat_time = time;
		ft_sleep(g_p.main[TE]);
		drop_forks(p);
	}
}

void	philo_sleep(t_philo *p)
{
	pthread_mutex_lock(&g_p.print_mutex);
	if (g_p.dead_flg == true)
	{
		pthread_mutex_unlock(&g_p.print_mutex);
		return ;
	}
	printf(YELLOW"%lld %d is sleeping\n"END, get_time(), p->id);
	pthread_mutex_unlock(&g_p.print_mutex);
	ft_sleep(g_p.main[TS]);
}

void	philo_think(t_philo *p)
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

void	*philosopher(void *arg)
{
	t_philo *p;

	p = (t_philo *)arg;
	ft_sleep(p->think_time);
	p->last_eat_time = get_time();
	while (g_p.dead_flg == false)
	{
		philo_eat(p);
		philo_think(p);
		philo_sleep(p);
	}
	return (NULL);
}

static int	loop_data(void)
{
	int	i;

	i = 0;
	while (++i <= g_p.main[PN])
	{
		pthread_create(&g_p.threads[i], NULL, philosopher, &g_p.philos[i]);
		// pthread_create(&g_p.monitors[i], NULL, monitor, &g_p.philos[i]);
	}
	i = 0;
	while (++i <= g_p.main[PN])
	{
		pthread_join(g_p.threads[i], NULL);
		// pthread_join(g_p.monitors[i], NULL);
	}
	i = 0;
	while (++i < g_p.main[PN])
	{
		pthread_detach(g_p.threads[i]);
		// pthread_detach(g_p.monitors[i]);
		pthread_mutex_destroy(&g_p.forks[i]);
	}
	pthread_mutex_destroy(&g_p.print_mutex);
	return (0);
}

int	main(int ac, char **av)
{
	if (check_args_and_store(ac, av))
		return (1);
	return (loop_data());
}
