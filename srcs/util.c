#include "philo.h"

int	ft_error_msg(const char *emsg)
{
	ft_putendl_fd((char *)emsg, 2);
	return (1);
}

void	set_philos_time(int sec)
{
	int	i;

	i = 0;
	while (i < g_p.main[PN])
	{
		g_p.philos[i].eat_time = sec;
		i++;
	}
}
