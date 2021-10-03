#include "philo.h"

int	ft_error_msg(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	write(2, s, len);
	write(2, "\n", 1);
	return (1);
}

void	ft_sleep(int64_t msec)
{
	int64_t	now;

	now = get_time();
	while (get_time() - now < msec)
	{
		usleep(900);
	}
}

bool	is_dead(t_philo *p, int64_t time)
{
	register int64_t	time_lag;
	register int		i;

	if (*p->dead_flg == true)
	{
		return (true);
	}
	i = 0;
	while (++i <= p->main[PN])
	{
		time_lag = time - p->last_eat_time[i];
		if (p->last_eat_time[i] != 0 && time_lag > p->main[TD])
		{
			printf(RED"%lld %d has died\n"END, time, i);
			*p->dead_flg = true;
			return (true);
		}
	}
	return (false);
}

// bool	is_dead(t_philo *p, int64_t time)
// {
// 	register bool	ret;

// 	pthread_mutex_lock(p->print_mutex);
// 	ret = is_dead_inner(p, time);
// 	pthread_mutex_unlock(p->print_mutex);
// 	return (ret);
// }
