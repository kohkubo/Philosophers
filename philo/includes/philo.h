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
# include <string.h>
# include <stdlib.h>
# define PN_MAX 210
# define DEBUG
enum	e_data
{
	PHILO_NUM = 1,
	TIME_DIE,
	TIME_EAT,
	TIME_SLEEP,
	EAT_COUNT,
	ANK
};
typedef struct s_philo
{
	int				id;
	int64_t			main[ANK];
	int				eat_count;
	int64_t			think_time;
	int64_t			first_think_time;
	int64_t			*last_eat_time;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*forks;
	bool			*dead_flg;
	int				fork_left;
	int				fork_right;
	bool			fork_left_flg;
	bool			fork_right_flg;
}	t_philo;
typedef struct s_data
{
	int64_t			main[ANK];
	t_philo			philos[PN_MAX];
	int64_t			last_eat_time[PN_MAX];
	pthread_t		threads[PN_MAX];
	pthread_mutex_t	forks[PN_MAX];
	pthread_mutex_t	mutex;
	bool			dead_flg;
}	t_data;

bool	drop_forks(t_philo *p);
bool	grab_fork_left(t_philo *p, int fork_id);
bool	grab_fork_right(t_philo *p, int fork_id);
bool	is_dead(t_philo *p, int64_t time, int id);
bool	is_dead_mutex(t_philo *p, int64_t time, int id);
bool	is_num_string(char *s);
bool	philo_act(t_philo *p, char *msgfmt, int64_t sleep_time, void (*f)());
bool	sleep_and_is_death(t_philo *p, int64_t msec, int id);
int		ft_atoi(const char *s);
int		ft_error_msg(const char *s);
int		loop_data(t_data *data);
int64_t	get_time(void);
void	philo_eat(t_philo *p, int64_t time);
void	store_args_data(t_data *data, int i);
#endif
