/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:51:38 by ywake             #+#    #+#             */
/*   Updated: 2021/08/28 16:51:05 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libex.h"
/*
** Check if the string array contains the string word.
** If it is contain, returns its index, otherwise returns -1.
*/
int	contain(char **array, char *word)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strcmp(array[i], word) == 0)
			return (i);
		i++;
	}
	return (-1);
}
