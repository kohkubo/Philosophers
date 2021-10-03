#include "philo.h"
#include <stdlib.h>

static void	*philosopher(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	pthread_mutex_lock(p->print_mutex);
	p->last_eat_time[p->id] = get_time();
	pthread_mutex_unlock(p->print_mutex);
	if (sleep_and_is_death(p, p->first_think_time))
	{
		return (NULL);
	}
	while (1)
	{
		if (grab_forks(p))
		{
			break ;
		}
		if (philo_act(p, p->main[TE], philo_eat))
		{
			break ;
		}
		if (drop_forks(p))
		{
			break ;
		}
		if (philo_act(p, p->main[TS], philo_sleep))
		{
			break ;
		}
		if (philo_act(p, p->think_time, philo_think))
		{
			break ;
		}
		// if (\
		// philo_act(p, 0, grab_fork_left) || \
		// philo_act(p, 0, grab_fork_right) || \
		// philo_act(p, p->main[TE], philo_eat) || \
		// drop_forks(p) || \
		// philo_act(p, p->main[TS], philo_sleep) || \
		// philo_act(p, p->think_time, philo_think))
		// 	break ;
	}
	return (NULL);
}

int	loop_data(t_data *data)
{
	int	i;

	if (data->main[PN] == 1)
	{
		// TODO
		ft_sleep(data->main[TD]);
		printf(RED"%lld %d has died\n"END, get_time(), 1);
		pthread_detach(data->threads[1]);
		pthread_mutex_destroy(&data->forks[1]);
		return (0);
	}
	i = 0;
	while (++i <= data->main[PN])
	{
		pthread_create(&data->threads[i], NULL, philosopher, &data->philos[i]);
	}
	i = 0;
	while (++i <= data->main[PN])
		pthread_join(data->threads[i], NULL);
	i = 0;
	while (++i <= data->main[PN])
	{
		pthread_detach(data->threads[i]);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->print_mutex);
	return (0);
}
