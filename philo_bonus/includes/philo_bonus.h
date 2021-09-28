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
# include <fcntl.h>
# include <stdint.h>
# include <stdbool.h>
# include <errno.h>
# include <stdlib.h>
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
	int			main[ANK];
	t_philo		philos[PN_MAX];
	pid_t		process[PN_MAX];
	sem_t		*forks;
	sem_t		*print_mutex;
	bool		dead_flg;
}				t_data;
extern t_data	g_p;
pid_t	ft_fork(void);
pid_t	ft_fork(void);
pid_t	ft_waitpid(pid_t pid);

bool	is_num_string(char *s);
int		ft_atoi(const char *s);
int64_t	get_time(void);
pid_t	ft_fork(void);
pid_t	ft_waitpid(pid_t pid);
void	drop_forks(t_philo *p);
void	ft_error_exit(const char *s);
void	ft_sleep(int64_t msec);
void	grab_forks(t_philo *p);
void	is_dead(int64_t time);
void	loop_data(void);
#endif
