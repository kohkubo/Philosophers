#include "philo_bonus.h"

void	ft_sleep(int64_t msec)
{
	register int64_t	now;

	now = get_time();
	while (get_time() - now < msec)
	{
		usleep(900);
	}
}

void	sleep_and_is_death(t_philo *p, int64_t msec)
{
	register int64_t	now;
	register int64_t	time;

	(void)p;
	now = get_time();
	while (1)
	{
		time = get_time();
		if (!(time - now < msec))
		{
			return ;
		}
		sem_wait(p->mutex);
		is_dead(p, time);
		sem_post(p->mutex);
		usleep(800);
	}
}

void	is_dead(t_philo *p, int64_t time)
{
	register int64_t	time_lag;
	register int		i;

	if (*p->dead_flg == true)
	{
		philo_exit(p);
	}
	i = 0;
	while (++i <= p->main[PN])
	{
		time_lag = time - p->last_eat_time[i];
		if (p->last_eat_time[i] != 0 && time_lag > p->main[TD])
		{
			printf(RED"%lld %d has died\n"END, time, i);
			*p->dead_flg = true;
			philo_exit(p);
		}
	}
}
