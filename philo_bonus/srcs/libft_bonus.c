#include "philo_bonus.h"

bool	is_num_string(char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (!('0' <= *s && *s <= '9'))
			return (false);
		s++;
	}
	return (true);
}

static int	ft_atoi_overflow(int neg)
{
	errno = EINVAL;
	if (neg == 1)
		return ((int)LONG_MAX);
	else
		return ((int)LONG_MIN);
}

int	ft_atoi(const char *s)
{
	unsigned long	n;
	int				neg;
	unsigned long	tmp;

	n = 0;
	neg = 1;
	while (('\t' <= *s && *s <= '\r') || *s == ' ')
		s++;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			neg = -1;
	while ('0' <= *s && *s <= '9')
	{
		tmp = n;
		n = n * 10 + *s++ - '0';
		if (tmp >> 60 || n >> 63)
			return (ft_atoi_overflow(neg));
	}
	if (n > INT_MAX || (n == (unsigned long)INT_MAX + 1 && neg == -1))
		errno = EINVAL;
	return ((int)(n * neg));
}

void	ft_error_exit(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	write(2, s, len);
	write(2, "\n", 1);
	sem_unlink("/mutex");
	sem_unlink("/forks");
	exit(1);
}

int	catch_error(int status, char *title)
{
	if (status == -1)
		ft_error_exit(title);
	return (status);
}
