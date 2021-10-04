#include "philo.h"

bool	is_dead(t_philo *p, int64_t time, int id)
{
	register int64_t	time_lag;

	if (*p->dead_flg == true)
	{
		return (true);
	}
	time_lag = time - p->last_eat_time[id];
	if ((p->last_eat_time[id] && time_lag > p->main[TD]))
	{
		printf(RED"[%lld] %lld %d has died\n"END, time_lag, time, id);
		*p->dead_flg = true;
		return (true);
	}
	return (false);
}

bool	is_dead_mutex(t_philo *p, int64_t time, int id)
{
	register bool	ret;

	pthread_mutex_lock(p->mutex);
	ret = is_dead(p, time, id);
	pthread_mutex_unlock(p->mutex);
	return (ret);
}

bool	sleep_and_is_death(t_philo *p, int64_t msec, int id)
{
	register int64_t	now;
	register int64_t	time;
	(void)id;
	(void)p;

	now = get_time();
	while (msec)
	{
		time = get_time();
		if (!(time - now < msec))
		{
			return (false);
		}
		// if (is_dead_mutex(p, time, id))
		// {
		// 	return (true);
		// }
		usleep(1000);
	}
	return (false);
}
