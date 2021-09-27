#ifndef PHILO_H
# define PHILO_H
# include "logging.h"
# include <pthread.h>
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
	pthread_mutex_t	forks[PN_MAX];
	pthread_mutex_t	print_mutex;
	bool			dead_flg;
}				t_data;
extern t_data	g_p;

bool	is_dead(int64_t time);
bool	is_num_string(char *s);
int		check_args_and_store(int ac, char **av);
int		check_nums_and_store(int ac, char **av);
int		ft_atoi(const char *s);
int		ft_error_msg(const char *s);
int		loop_data(void);
int		print_usage(void);
int64_t	get_time(void);
void	*philosopher(void *arg);
void	drop_forks(t_philo *p);
void	ft_sleep(int64_t msec);
void	grab_forks(t_philo *p);
void	init_philo(void);
void	philo_action(t_philo *p, char *msg_fmt, int sleep_time);
void	philo_eat(t_philo *p);
#endif
