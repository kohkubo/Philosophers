#include "philo_bonus.h"

# define CHILD 0

static void	philo_eat(t_philo *p)
{
	int64_t	time;

	sem_wait(g_p.print_mutex);
	grab_forks(p);
	time = get_time();
	if (is_dead(time))
	{
		sem_post(g_p.print_mutex);
		exit(0);
	}
	printf(BLUE"%lld %d is eating\n"END, time, p->id);
	p->last_eat_time = time;
	sem_post(g_p.print_mutex);
	if (g_p.main[EC] != -1 && ++p->eat_count > g_p.main[EC])
		g_p.dead_flg = true;
	ft_sleep(g_p.main[TE]);
	drop_forks(p);
}

static void	philo_action(t_philo *p, char *msg_fmt, int sleep_time)
{
	int64_t	time;

	sem_wait(g_p.print_mutex);
	time = get_time();
	if (is_dead(time))
	{
		sem_post(g_p.print_mutex);
		exit(0);
	}
	printf(msg_fmt, time, p->id);
	sem_post(g_p.print_mutex);
	ft_sleep(sleep_time);
}

static void	*philosopher(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	sem_wait(g_p.print_mutex);
	p->last_eat_time = get_time();
	sem_post(g_p.print_mutex);
	ft_sleep(p->first_think_time);
	while (1)
	{
		philo_eat(p);
		philo_action(p, YELLOW"%lld %d is sleeping\n"END, g_p.main[TS]);
		philo_action(p, MAGENTA"%lld %d is thinking\n"END, p->think_time);
	}
	return (NULL);
}

void	loop_data(void)
{
	int	i;

	if (g_p.main[PN] == 1)
	{
		ft_sleep(g_p.main[TD]);
		printf(RED"%lld %d has died\n"END, get_time(), 1);
		sem_close(g_p.forks);
		sem_close(g_p.print_mutex);
		exit(0);
	}
	i = 0;
	while (++i <= g_p.main[PN])
	{
		g_p.process[i] = ft_fork();
		if (g_p.process[i] == CHILD)
			philosopher(&g_p.philos[i]);
	}
	i = 0;
	while (++i <= g_p.main[PN])
	{
		waitpid(g_p.process[i], NULL, 0);
	}
	i = 0;
	sem_close(g_p.forks);
	sem_close(g_p.print_mutex);
}
