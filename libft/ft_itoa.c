/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 15:17:50 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/04/14 12:23:38 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <limits.h>

int	positive(int j)
{
	if (j < 0)
		j *= -1;
	return (j);
}

char	*ft_itoa(int n)
{
	size_t	i;
	int		j;
	char	buf[12];

	i = 11;
	buf[11] = '\0';
	while (1)
	{
		j = n % 10;
		i--;
		buf[i] = '0' + positive(j);
		n = n / 10;
		if (n == 0)
			break ;
	}
	if (j < 0)
	{
		i--;
		buf[i] = '-';
	}
	return (ft_strdup(buf + i));
}
