#include "philo.h"

static int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

bool	is_num_string(char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
		if (!ft_isdigit(*s++))
			return (false);
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
	while (ft_isdigit(*s))
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
