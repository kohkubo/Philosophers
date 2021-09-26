#include "philo.h"

void	*monitor(void *arg)
{
	t_philo *p;

	p = (t_philo *)arg;
	while (g_p.dead_flg == false)
	{
		ft_sleep(g_p.main[TD]);
		int64_t time = get_time();
		int64_t time_lag = time - p->last_eat_time;
		if (time_lag >= g_p.main[TD])
		{
			pthread_mutex_lock(&g_p.print_mutex);
			g_p.dead_flg = true;
#ifdef DEBUG
			printf(RED"%lld %d has died [%lld]\n"END, time, p->id, time_lag);
#else
			printf(RED"%lld %d has died\n"END, time, p->id);
#endif
			pthread_mutex_unlock(&g_p.print_mutex);
			break ;
		}
	}
	return (NULL);
}
