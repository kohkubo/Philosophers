#include "philo_bonus.h"

int64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

sem_t	*ft_sem_open(char *name, int value)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem == SEM_FAILED)
		ft_error_exit("sem_open failed");
	return (sem);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error_exit("Fork error");
	return (pid);
}

void	store_sleeptime(t_data *data, int i)
{
	if (data->main[PHILO_NUM] % 2 == 0)
	{
		if (i % 2 != 0)
			data->philos[i].first_think_time = data->main[TIME_EAT];
	}
	else
	{
		if (i % 3 == 0)
			data->philos[i].first_think_time = data->main[TIME_EAT];
		else if (i % 3 == 1)
			data->philos[i].first_think_time = data->main[TIME_EAT] * 2;
		data->philos[i].think_time = 10;
	}
}

void	sem_unlink_all(void)
{
	sem_unlink("/mutex");
	sem_unlink("/forks");
	sem_unlink("/dead");
	sem_unlink("/eat_count");
}
