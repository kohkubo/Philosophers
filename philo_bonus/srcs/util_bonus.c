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

void	philo_exit(void)
{
	sem_post(g_p.dead);
	exit(0);
}

void	kill_all(void)
{
	int		i;

	i = 0;
	while (++i <= g_p.main[PN])
	{
		if (g_p.process[i] != 0)
		{
			kill(g_p.process[i], SIGKILL);
			g_p.process[i] = 0;
		}
	}
}
