/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: david <david@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/18 15:26:06 by david         #+#    #+#                 */
/*   Updated: 2021/11/04 15:14:38 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((str2[i] != '\0' && *str2 != '\0') && n - 1 > 0)
	{
		if (str2[i] != str1[i])
			break ;
		n--;
		i++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
