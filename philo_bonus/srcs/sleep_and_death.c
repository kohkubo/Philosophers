#include "philo_bonus.h"

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
		is_dead(p, time, p->id);
		sem_post(p->mutex);
		usleep(800);
	}
}

void	is_dead(t_philo *p, int64_t time, int id)
{
	if (*p->dead_flg == true)
	{
		philo_exit(p);
	}
	if ((p->last_eat_time[id] && time - p->last_eat_time[id] > p->main[TD]))
	{
		printf(RED"%lld %03d has died\n"END, time, id);
		*p->dead_flg = true;
		philo_exit(p);
	}
}

void	philo_exit(t_philo *p)
{
	printf("philo_exit\n");
	sem_post(p->dead);
	if (p->main[EC] != -1)
		sem_post(p->mutex);
	exit(0);
}

void	kill_all(t_data *data)
{
	int		i;

	i = 0;
	while (++i <= data->main[PN])
	{
		if (data->process[i] != 0)
		{
			kill(data->process[i], SIGKILL);
			data->process[i] = 0;
		}
	}
}
