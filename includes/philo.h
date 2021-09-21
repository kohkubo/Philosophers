#ifndef PHILO_H
# define PHILO_H
# include "libft.h"
# include "libex.h"
# include "logging.h"
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# define PN_MAX 300
enum	e_data
{
	PN = 1,
	TD,
	TE,
	TS,
	EC,
	ANK
};
typedef enum e_status
{
	GRAB = 0,
	EAT,
	THINK,
	SLEEP,
	DIE
}				t_status;
typedef struct s_philo
{
	int			id;
	t_status	status;
	int			eat_count;
	int64_t		last_eat_time;
	int			fork_left;
	int			fork_right;
}				t_philo;
typedef struct s_data
{
	int				main[ANK];
	t_philo			philos[PN_MAX];
	pthread_t		threads[PN_MAX];
	pthread_t		monitor;
	pthread_mutex_t	forks[PN_MAX];
	pthread_mutex_t	print_mutex;
	bool			dead_flg;
	struct timeval	die_to_time;
	struct timeval	start_time;
	struct timeval	now_time;
}				t_data;
extern t_data	g_p;

int		check_args_and_store(int ac, char **av);
int		check_nums_and_store(int ac, char **av);
int		ft_error_msg(const char *emsg);
int		main(int ac, char **av);
int		print_usage(void);
int64_t	get_time(void);
void	*monitor(void *arg);
void	*philosopher(void *arg);
void	debug_print(void);
void	drop_forks(t_philo *p);
void	grab_forks(t_philo *p);
void	print_status(t_philo *p, t_status status);
void	set_philos_time(int sec);
#endif
