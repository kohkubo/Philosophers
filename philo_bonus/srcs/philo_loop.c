#include "philo_bonus.h"

# define CHILD 0

void grab_fork(t_philo *p, int64_t time)
{
	(void)p;
	(void)time;
	sem_wait(g_p.forks);
}

void ft_void(t_philo *p, int64_t time)
{
	(void)p;
	(void)time;
}

void eat(t_philo *p, int64_t time)
{
	if (g_p.main[EC] != -1 && ++p->eat_count > g_p.main[EC])
	{
		g_p.dead_flg = true;
		kill_all(p->id);
		printf("a3\n");
		exit(0);
	}
	p->last_eat_time = time;
}

void	philo_action(t_philo *p, char *msg_fmt, int sleep_time, void (*f)(t_philo *, int64_t))
{
	int64_t	time;

	sem_wait(g_p.print_mutex);
	time = get_time();
	is_dead(time, p);
	f(p, time);
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
		philo_action(p, GREEN"%lld %d has taken a fork\n"END, 0, grab_fork);
		philo_action(p, GREEN"%lld %d has taken a fork\n"END, 0, grab_fork);
		philo_action(p, BLUE"%lld %d is eating\n"END, g_p.main[TE], eat);
		drop_forks();
		philo_action(p, YELLOW"%lld %d is sleeping\n"END, g_p.main[TS], ft_void);
		philo_action(p, MAGENTA"%lld %d is thinking\n"END, p->think_time, ft_void);
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
