/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 14:28:57 by dyeboa        #+#    #+#                 */
/*   Updated: 2021/11/15 15:23:50 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*newb;

	newb = (unsigned char *)b;
	while (n-- > 0)
		newb[n] = (unsigned char)c;
	return (b);
}
