#include "philo.h"

t_data	g_p = {};

void print_status(t_philo *p, t_status status)
{
	if (g_p.dead_flg == true)
		return ;
	pthread_mutex_lock(&(g_p.print_mutex));
	if (status == EAT)
	{
		grab_forks(p);
		printf("%lld %d has taken a fork\n", get_time(), p->id);
		int64_t time = get_time();
		int64_t time_lag = time - p->last_eat_time;
		// if (0)
		if (time_lag >= g_p.main[TD])
		{
			printf(RED"%lld %d has died [%lld]\n"END, time, p->id, time_lag);
			g_p.dead_flg = true;
		}
		else
		{
			printf("%lld %d is eating [%lld]\n", time, p->id, time_lag);
			p->last_eat_time = time;
			usleep(g_p.main[TE] * 1000);
			drop_forks(p);
		}
	}
	else if (status == SLEEP)
	{
		printf("%lld %d is sleeping\n", get_time(), p->id);
		usleep(g_p.main[TS] * 1000);
	}
	else if (status == THINK)
	{
		printf("%lld %d is thinking\n", get_time(), p->id);
		usleep(g_p.main[TS] * 1000);
	}
	pthread_mutex_unlock(&(g_p.print_mutex));
	if (g_p.dead_flg == true)
		return ;
}

void	*philosopher(void *arg)
{
	t_philo *p;

	p = (t_philo *)arg;
	printf("booooooooooooooooon\n");
	p->last_eat_time = get_time();
	if (p->id % 2 == 0)
	{
		usleep(g_p.main[TE] * 1000);
	}
	printf("g_p.dead_flg : %d\n", g_p.dead_flg);
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
	printf("%d start\n", g_p.start_time.tv_usec);
	set_philos_time(g_p.start_time.tv_usec);
	if (gettimeofday(&g_p.now_time, NULL) == -1)
		return (ft_error_msg("gettimeofday() failed"));
	i = 0;
	while (++i <= g_p.main[PN])
		pthread_create(&g_p.threads[i], NULL, philosopher, &g_p.philos[i]);
	i = 0;
	while (++i <= g_p.main[PN])
		pthread_join(g_p.threads[i], NULL);
	// pthread_create(&g_p.monitor, NULL, monitor, NULL);
	// pthread_detach(g_p.monitor);
	return (0);
}

int	main(int ac, char **av)
{
	if (check_args_and_store(ac, av))
		return (1);
	return (loop_data());
}
