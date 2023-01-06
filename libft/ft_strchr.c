/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 14:53:48 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/01/24 15:18:14 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = ft_strlen(s);
	if (c == 0)
		return ((char *)s + i);
	while (j <= i)
	{
		if (s[j] == (char) c)
			return ((char *)s + j);
		j++;
	}
	return (0);
}
