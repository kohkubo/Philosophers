#include "libex.h"

bool	is_available_pid(int pid)
{
	errno = 0;
	kill(pid, 0);
	if (errno)
		return (false);
	return (true);
}
