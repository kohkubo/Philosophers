#include "philo.h"

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

void	store_args_data(t_data *data, int i)
{
	data->philos[i].last_eat_time = data->last_eat_time;
	data->philos[i].dead_flg = &data->dead_flg;
	data->philos[i].mutex = &data->mutex;
	data->philos[i].forks = data->forks;
	data->philos[i].main[PHILO_NUM] = data->main[PHILO_NUM];
	data->philos[i].main[TIME_DIE] = data->main[TIME_DIE];
	data->philos[i].main[TIME_EAT] = data->main[TIME_EAT];
	data->philos[i].main[TIME_SLEEP] = data->main[TIME_SLEEP];
	data->philos[i].main[EAT_COUNT] = data->main[EAT_COUNT];
}
