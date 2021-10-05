#include "philo.h"

bool	grab_fork_left(t_philo *p, int fork_id)
{
	pthread_mutex_lock(&(p->forks[fork_id]));
	p->fork_left_flg = true;
	return (philo_act(p, GREEN"%lld %03d has taken a fork\n"END, 0, NULL));
}

bool	grab_fork_right(t_philo *p, int fork_id)
{
	pthread_mutex_lock(&(p->forks[fork_id]));
	p->fork_right_flg = true;
	return (philo_act(p, GREEN"%lld %03d has taken a fork\n"END, 0, NULL));
}

void	philo_eat(t_philo *p, int64_t time)
{
	p->last_eat_time[p->id] = time;
	if (p->main[EAT_COUNT] != -1 && ++p->eat_count > p->main[EAT_COUNT])
		*p->dead_flg = true;
}

bool	drop_forks(t_philo *p)
{
	pthread_mutex_unlock(&(p->forks[p->fork_left]));
	p->fork_left_flg = false;
	pthread_mutex_unlock(&(p->forks[p->fork_right]));
	p->fork_right_flg = false;
	return (false);
}

bool	philo_act(t_philo *p, char *msgfmt, int64_t sleep_time, void (*f)())
{
	register int64_t	time;

	pthread_mutex_lock(p->mutex);
	time = get_time();
	if (is_dead(p, time, p->id))
	{
		pthread_mutex_unlock(p->mutex);
		return (true);
	}
	printf(msgfmt, time, p->id);
	if (f)
		f(p, time);
	pthread_mutex_unlock(p->mutex);
	return (sleep_and_is_death(p, sleep_time, p->fork_right));
}
