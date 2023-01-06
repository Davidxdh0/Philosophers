/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/23 13:58:21 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/08/23 14:03:12 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	convert_base(char *str, char *base)
{
	int	i;
	int	j;
	int	number;
	int	len;

	i = 0;
	j = 0;
	number = 0;
	len = ft_strlen(base);
	while (str[i] && ft_strchr(base, str[i]))
	{
		j = 0;
		while (base[j] != str[i] && base[j])
			j++;
		number = (number * len) + j;
		i++;
	}
	return (number);
}

int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

int	ft_atoi_base(char *str, char *base)
{
	int			i;
	int			minorplus;
	int			number;

	number = 0;
	i = 0;
	minorplus = 1;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			minorplus *= -1;
		if (str[i] == '-' || str[i] == '+')
			return (0);
	}
	if (str[i] == '0')
	{
		i++;
		if (str[i] == 'X' || str[i] == 'x')
			i++;
	}
	number = convert_base(&str[i], base);
	return (number * minorplus);
}
