#include "philo_bonus.h"

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

void	philo_exit(t_philo *p)
{
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

void	store_sleeptime(t_data *data, int i)
{
	if (data->main[PN] % 2 == 0)
	{
		if (i % 2 != 0)
			data->philos[i].first_think_time = data->main[TE];
	}
	else
	{
		if (i % 3 == 0)
			data->philos[i].first_think_time = data->main[TE];
		else if (i % 3 == 1)
			data->philos[i].first_think_time = data->main[TE] * 2;
		data->philos[i].think_time = 10;
	}
}
