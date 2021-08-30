#ifndef PHILO_H
# define PHILO_H
# include "libft.h"
# include "libex.h"
# include <pthread.h>
# define PN_MAX 300
enum	e_data
{
	PN = 0,
	TD,
	TE,
	TS,
	EC,
	ANK
};
typedef enum e_status
{
	EAT = 0,
	THINK,
	SLEEP,
	DIE
}				t_status;
typedef struct s_philo
{
	int			id;
	t_status	status;
	int			eat_count;
	int			eat_time;
	bool		fork_left;
	bool		fork_right;
}				t_philo;
typedef struct s_data
{
	int				main[ANK];
	t_philo			philos[PN_MAX];
	struct timeval	start_time;
	struct timeval	now_time;
}				t_data;
extern t_data	g_p;

int		ft_error_msg(const char *emsg);
int		main(int ac, char **av);
void	set_philos_time(int sec);
#endif
