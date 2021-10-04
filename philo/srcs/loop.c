#include "philo.h"
#include <stdlib.h>

static void	*philosopher(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	pthread_mutex_lock(p->mutex);
	p->last_eat_time[p->id] = get_time();
	pthread_mutex_unlock(p->mutex);
	if (sleep_and_is_death(p, p->first_think_time, p->id))
		return (NULL);
	while (1)
	{
		if (grab_fork_left(p, p->fork_left) || \
		grab_fork_right(p, p->fork_right) || \
		philo_act(p, BLUE"%lld %03d is eating\n"END, p->main[TE], philo_eat) || \
		drop_forks(p) || \
		philo_act(p, YELLOW"%lld %03d is sleeping\n"END, p->main[TS], NULL) || \
		philo_act(p, MAGENTA"%lld %03d is thinking\n"END, p->think_time, NULL))
		{
			break ;
		}
	}
	if (p->fork_left_flg == true)
		pthread_mutex_unlock(&(p->forks[p->fork_left]));
	if (p->fork_right_flg == true)
		pthread_mutex_unlock(&(p->forks[p->fork_right]));
	return (NULL);
}

int	loop_data(t_data *data)
{
	int	i;

	if (data->main[PN] == 1)
	{
		ft_sleep(data->main[TD]);
		printf(RED"%lld %d has died\n"END, get_time(), 1);
		pthread_detach(data->threads[1]);
		pthread_mutex_destroy(&data->forks[1]);
		return (0);
	}
	i = 0;
	while (++i <= data->main[PN])
		pthread_create(&data->threads[i], NULL, philosopher, &data->philos[i]);
	i = 0;
	while (++i <= data->main[PN])
		pthread_join(data->threads[i], NULL);
	i = 0;
	while (++i <= data->main[PN])
	{
		pthread_detach(data->threads[i]);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->mutex);
	return (0);
}
