/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:03:39 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/23 22:48:06 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	ft_write(int fildes, const void *buf, size_t nbyte)
{
	return (write(fildes, buf, nbyte));
}

void	ft_putstr_fd(char *s, int fd)
{
	ft_write(fd, s, ft_strlen(s));
}
