#include "philo_bonus.h"

int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	grab_fork(t_philo *p, int64_t time)
{
	(void)p;
	(void)time;
	sem_wait(g_p.forks);
}

void	drop_forks(void)
{
	sem_post(g_p.forks);
	sem_post(g_p.forks);
}

void	ft_void(t_philo *p, int64_t time)
{
	(void)p;
	(void)time;
}

void	eat(t_philo *p, int64_t time)
{
	if (g_p.main[EC] != -1 && ++p->eat_count > g_p.main[EC])
	{
		g_p.dead_flg = true;
		philo_exit();
	}
	p->last_eat_time = time;
}
