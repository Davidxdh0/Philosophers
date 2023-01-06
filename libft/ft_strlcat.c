/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/09 12:00:59 by dyeboa        #+#    #+#                 */
/*   Updated: 2021/12/16 12:43:34 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t		len_dest;
	const char	*tempsrc;
	char		*tempdest;
	size_t		tempsize;

	tempdest = dest;
	tempsrc = src;
	tempsize = dstsize;
	while (tempsize-- != 0 && *tempdest != '\0')
		tempdest++;
	len_dest = tempdest - dest;
	tempsize = dstsize - len_dest;
	if (tempsize == 0)
		return (len_dest + ft_strlen(tempsrc));
	while (*tempsrc != '\0')
	{
		if (tempsize != 1)
		{
			*tempdest++ = *tempsrc;
			tempsize--;
		}
		tempsrc++;
	}
	*tempdest = '\0';
	return (len_dest + tempsrc - src);
}
