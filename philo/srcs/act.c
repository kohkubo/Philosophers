#include "philo.h"

int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// void	grab_fork_left(t_philo *p, int64_t time)
// {
// 	pthread_mutex_unlock(p->print_mutex);
// 	pthread_mutex_lock(&(p->forks[p->fork_left]));
// 	pthread_mutex_lock(p->print_mutex);
// 	printf(GREEN"%lld %d has taken a fork\n"END, time, p->id);
// }

// void	grab_fork_right(t_philo *p, int64_t time)
// {
// 	pthread_mutex_unlock(p->print_mutex);
// 	pthread_mutex_lock(&(p->forks[p->fork_right]));
// 	pthread_mutex_lock(p->print_mutex);
// 	printf(GREEN"%lld %d has taken a fork\n"END, time, p->id);
// }

bool	grab_forks(t_philo *p)
{
	int64_t	time;

	pthread_mutex_lock(&(p->forks[p->fork_left]));
	time = get_time();
	pthread_mutex_lock(p->print_mutex);
	if (is_dead(p, time))
	{
		pthread_mutex_unlock(p->print_mutex);
		return (true);
	}
	printf(GREEN"%lld %d has taken a fork\n"END, time, p->id);
	pthread_mutex_unlock(p->print_mutex);

	pthread_mutex_lock(&(p->forks[p->fork_right]));
	time = get_time();
	pthread_mutex_lock(p->print_mutex);
	if (is_dead(p, time))
	{
		pthread_mutex_unlock(p->print_mutex);
		return (true);
	}
	printf(GREEN"%lld %d has taken a fork\n"END, time, p->id);
	pthread_mutex_unlock(p->print_mutex);
	return (false);
}

void	philo_sleep(t_philo *p, int64_t time)
{
	printf(YELLOW"%lld %d is sleeping\n"END, time, p->id);
}

void	philo_think(t_philo *p, int64_t time)
{
	printf(MAGENTA"%lld %d is thinking\n"END, time, p->id);
}

void	philo_eat(t_philo *p, int64_t time)
{
	p->last_eat_time[p->id] = time;
	if (p->main[EC] != -1 && ++p->eat_count > p->main[EC])
		*p->dead_flg = true;
	printf(BLUE"%lld %d is eating\n"END, time, p->id);
}

bool	drop_forks(t_philo *p)
{
	pthread_mutex_unlock(&(p->forks[p->fork_left]));
	pthread_mutex_unlock(&(p->forks[p->fork_right]));
	return (false);
}

bool	sleep_and_is_death(t_philo *p, int64_t msec)
{
	register int64_t	now;
	register int64_t	time;

	now = get_time();
	while (1)
	{
		time = get_time();
		if (!(time - now < msec))
		{
			return (false);
		}
		pthread_mutex_lock(p->print_mutex);
		if (is_dead(p, time))
		{
			pthread_mutex_unlock(p->print_mutex);
			return (true);
		}
		pthread_mutex_unlock(p->print_mutex);
		usleep(1000);
	}
}

bool	philo_act(t_philo *p, int sleep_time, void (*f)(t_philo *, int64_t))
{
	register int64_t	time;

	time = get_time();
	pthread_mutex_lock(p->print_mutex);
	if (is_dead(p, time))
	{
		pthread_mutex_unlock(p->print_mutex);
		return (true);
	}
	f(p, time);
	pthread_mutex_unlock(p->print_mutex);
	if (sleep_and_is_death(p, sleep_time))
	{
		return (true);
	}
	return (false);
}
