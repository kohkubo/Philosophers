#include "philo_bonus.h"

void	philo_act(t_philo *p, char *msg_fmt, int sleep_time, void (*f)())
{
	register int64_t	time;

	sem_wait(p->mutex);
	time = get_time();
	is_dead(p, time, p->id);
	printf(msg_fmt, time, p->id);
	f(p, time);
	sem_post(p->mutex);
	sleep_and_is_death(p, sleep_time);
}

void	grab_fork(t_philo *p)
{
	int64_t	time;

	sem_wait(p->forks);
	sem_wait(p->mutex);
	time = get_time();
	is_dead(p, time, p->id);
	printf(GREEN"%lld %03d has taken a fork\n"END, time, p->id);
	sem_post(p->mutex);
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
	if (p->main[EAT_COUNT] != -1 && ++p->eat_count >= p->main[EAT_COUNT])
	{
		sem_post(p->eat_count_sem);
		drop_forks(p);
		sem_post(p->mutex);
		exit(0);
	}
	p->last_eat_time[p->id] = time;
}
