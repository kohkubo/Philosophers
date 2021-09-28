#ifndef PHILO_H
# define PHILO_H
# include "logging.h"
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdint.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# define PN_MAX 210
# define DEBUG
enum	e_data
{
	PN = 1,
	TD,
	TE,
	TS,
	EC,
	ANK
};
typedef struct s_philo
{
	int			id;
	int			eat_count;
	int64_t		last_eat_time;
	int64_t		think_time;
	int64_t		first_think_time;
	int			fork_left;
	int			fork_right;
}				t_philo;
typedef struct s_data
{
	int				main[ANK];
	t_philo			philos[PN_MAX];
	pthread_t		threads[PN_MAX];
	sem_t			*forks;
	sem_t			*print_mutex;
	bool			dead_flg;
}				t_data;
extern t_data	g_p;

bool	grab_forks(t_philo *p);
bool	is_dead(int64_t time);
bool	is_num_string(char *s);
int		check_args_and_store(int ac, char **av);
int		check_nums_and_store(int ac, char **av);
int		ft_atoi(const char *s);
int		ft_error_msg(const char *s);
int		print_usage(void);
int64_t	get_time(void);
void	drop_forks(t_philo *p);
void	ft_sleep(int64_t msec);
void	init_philo(void);
#endif
