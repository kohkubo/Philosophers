#include "philo_bonus.h"
#define CHILD 0

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
		sem_wait(p->print_mutex);
		is_dead(p, time);
		sem_post(p->print_mutex);
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

static void	philo_act(t_philo *p, char *msg_fmt, int sleep_time, void \
(*f)(t_philo *, int64_t))
{
	register int64_t	time;

	sem_wait(p->print_mutex);
	time = get_time();
	is_dead(p, time);
	f(p, time);
	printf(msg_fmt, time, p->id);
	sem_post(p->print_mutex);
	sleep_and_is_death(p, sleep_time);
}

static void	philosopher(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	sem_wait(p->print_mutex);
	if (*p->dead_flg == true)
	{
		exit(0);
	}
	p->last_eat_time[p->id] = get_time();
	sem_post(p->print_mutex);
	sleep_and_is_death(p, p->first_think_time);
	while (1)
	{
		grab_forks(p);
		philo_act(p, BLUE"%lld %d is eating\n"END, p->main[TE], eat);
		drop_forks(p);
		philo_act(p, YELLOW"%lld %d is sleeping\n"END, p->main[TS], ft_void);
		philo_act(p, MAGENTA"%lld %d is thinking\n"END, p->think_time, ft_void);
	}
	exit(0);
}

void	loop_data(t_data *data)
{
	int	i;

	if (data->main[PN] == 1)
	{
		ft_sleep(data->main[TD]);
		printf(RED"%lld %d has died\n"END, get_time(), 1);
		sem_unlink("/print_mutex");
		sem_unlink("/forks");
		sem_unlink("/dead");
		exit(0);
	}
	i = 0;
	while (++i <= data->main[PN])
	{
		data->process[i] = ft_fork();
		if (data->process[i] == CHILD)
		{
			philosopher(&data->philos[i]);
		}
	}
	sem_wait(data->dead);
	kill_all(data);
	sem_unlink("/print_mutex");
	sem_unlink("/forks");
	sem_unlink("/dead");
}
