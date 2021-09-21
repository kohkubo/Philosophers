#include "philo.h"

// void	*monitor(void *arg)
// {
// 	int	i;

// 	(void)arg;
// 	i = 1;
// 	while (1)
// 	{
// 		int64_t time = get_time();
// 		if (time - g_p.philos[i].last_eat_time >= g_p.main[TD])
// 		{
// 			printf(RED"%lld %d has died [%lld]\n"END, time, g_p.philos[i].id, time - g_p.philos[i].last_eat_time);
// 			g_p.dead_flg = true;
// 			return NULL;
// 		}
// 		i++;
// 		if (i > g_p.main[PN])
// 			i = 1;
// 	}
// }
