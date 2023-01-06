/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 15:04:13 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/02/02 13:04:55 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*charstring;

	i = 0;
	charstring = (unsigned char *)s;
	while (i < n)
	{
		if ((unsigned char) c == charstring[i])
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
