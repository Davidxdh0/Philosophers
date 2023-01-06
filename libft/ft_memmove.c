/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yeboa <yeboa@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/14 22:51:37 by yeboa         #+#    #+#                 */
/*   Updated: 2021/04/14 23:31:00 by yeboa         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*new_dst;
	char		*new_src;

	new_dst = (char *)dest;
	new_src = (char *)src;
	if (dest < src)
		ft_memcpy(dest, src, n);
	else if (dest > src)
	{
		while (n--)
			new_dst[n] = new_src[n];
	}
	return ((void *)dest);
}
