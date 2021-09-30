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
	if ((sem = sem_open(name, O_CREAT | O_EXCL, 0644, value)) == SEM_FAILED)
		ft_error_exit("sem_open failed");
	return (sem);
}
