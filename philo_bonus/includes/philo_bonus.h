#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include "logging.h"
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdint.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdbool.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
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
	int			main[ANK];
	int			eat_count;
	int64_t		think_time;
	int64_t		first_think_time;
	int64_t		*last_eat_time;
	sem_t		*forks;
	sem_t		*mutex;
	sem_t		*dead;
	bool		*dead_flg;
	int			fork_left;
	int			fork_right;
}				t_philo;
typedef struct s_data
{
	int			main[ANK];
	t_philo		philos[PN_MAX];
	int64_t		last_eat_time[PN_MAX];
	pid_t		process[PN_MAX];
	sem_t		*forks;
	sem_t		*mutex;
	sem_t		*dead;
	bool		dead_flg;
}				t_data;

bool	is_num_string(char *s);
int		catch_error(int status, char *title);
int		ft_atoi(const char *s);
int64_t	get_time(void);
pid_t	ft_fork(void);
sem_t	*ft_sem_open(char *name, int value);
void	drop_forks(t_philo *p);
void	eat(t_philo *p, int64_t time);
void	ft_error_exit(const char *s);
void	ft_sleep(int64_t msec);
void	ft_void(t_philo *p, int64_t time);
void	grab_fork(t_philo *p);
void	is_dead(t_philo *p, int64_t time);
void	kill_all(t_data *data);
void	loop_data(t_data *data);
void	philo_exit(t_philo *p);
void	sleep_and_is_death(t_philo *p, int64_t msec);
void	store_sleeptime(t_data *data, int i);
#endif
