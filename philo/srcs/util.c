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

int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
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

void	ft_sleep_philo(t_philo *p, int64_t msec)
{
	int64_t	now;

	now = get_time();
	while (get_time() - now < msec)
	{
		pthread_mutex_lock(p->mutex);
		if (*p->dead_flg == 0)
		{
			pthread_mutex_unlock(p->mutex);
			break ;
		}
		pthread_mutex_unlock(p->mutex);
		usleep(900);
	}
}

void	store_args_data(t_data *data, int i)
{
	data->philos[i].last_eat_time = data->last_eat_time;
	data->philos[i].dead_flg = &data->dead_flg;
	data->philos[i].mutex = &data->mutex;
	data->philos[i].forks = data->forks;
	data->philos[i].main[PN] = data->main[PN];
	data->philos[i].main[TD] = data->main[TD];
	data->philos[i].main[TE] = data->main[TE];
	data->philos[i].main[TS] = data->main[TS];
	data->philos[i].main[EC] = data->main[EC];
}
