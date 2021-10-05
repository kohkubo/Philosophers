#include "philo_bonus.h"
#define CHILD 0

static void	philosopher(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	sem_wait(p->mutex);
	if (*p->dead_flg == true)
	{
		exit(0);
	}
	p->last_eat_time[p->id] = get_time();
	sem_post(p->mutex);
	sleep_and_is_death(p, p->first_think_time);
	while (1)
	{
		grab_fork(p);
		grab_fork(p);
		philo_act(p, BLUE"%lld %03d is eating\n"END, p->main[TIME_EAT], eat);
		drop_forks(p);
		philo_act(p, YELLOW"%lld %03d is sleeping\n"END, p->main[TIME_SLEEP], ft_void);
		philo_act(p, MAGENTA"%lld %03d is thinking\n"END, \
		p->think_time, ft_void);
	}
	exit(0);
}

void	loop_data(t_data *data)
{
	int	i;

	if (data->main[PHILO_NUM] == 1)
	{
		usleep(data->main[TIME_DIE] * 1000);
		printf(RED"%lld %03d has died\n"END, get_time(), 1);
		sem_unlink_all(), exit(0);
	}
	i = 0;
	while (++i <= data->main[PHILO_NUM])
	{
		data->process[i] = ft_fork();
		if (data->process[i] == CHILD)
			philosopher(&data->philos[i]);
	}
	if (data->main[EC] != -1)
	{
		i = 0;
		while (++i <= data->main[PHILO_NUM])
			sem_wait(data->eat_count_sem);
		sem_post(data->dead);
	}
	sem_wait(data->dead);
	kill_all(data), sem_unlink_all();
}
