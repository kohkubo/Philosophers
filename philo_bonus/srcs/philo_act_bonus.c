#include "philo_bonus.h"

int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	grab_forks(t_philo *p)
{
	int64_t	time;

	sem_wait(p->forks);
	time = get_time();
	sem_wait(p->print_mutex);
	is_dead(p, time);
	printf(GREEN"%lld %d has taken a fork\n"END, time, p->id);
	sem_post(p->print_mutex);

	sem_wait(p->forks);
	time = get_time();
	sem_wait(p->print_mutex);
	is_dead(p, time);
	printf(GREEN"%lld %d has taken a fork\n"END, time, p->id);
	sem_post(p->print_mutex);
}

void	grab_fork(t_philo *p, int64_t time)
{
	(void)time;
	sem_wait(p->forks);
}

void	drop_forks(t_philo *p)
{
	sem_post(p->forks);
	sem_post(p->forks);
}

void	ft_void(t_philo *p, int64_t time)
{
	(void)p;
	(void)time;
}

void	eat(t_philo *p, int64_t time)
{
	if (p->main[EC] != -1 && ++p->eat_count > p->main[EC])
	{
		if (p->eat_count == p->main[EC] + 1)
			philo_exit(p);
		exit(0);
	}
	p->last_eat_time[p->id] = time;
}
