/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 14:18:48 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/08/19 12:31:31 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int	is_newline(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

// returns the text without what is printed.
char	*new_text(char	*text)
{
	int		i;
	int		len;
	char	*new_text;

	i = 0;
	len = 0;
	while (text[len] != '\n' && text[len] != '\0')
		len++;
	if (!text[len])
	{
		free(text);
		return (NULL);
	}
	new_text = malloc(ft_strlen(text) + 1);
	if (!(new_text))
		return (0);
	while (text[len++])
		new_text[i++] = text[len];
	new_text[i] = '\0';
	free(text);
	return (new_text);
}

//returns line
char	*get_line(char	*text)
{
	char	*line;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (!text[len])
		return (NULL);
	while (text[len] != '\n' && text[len] != '\0')
		len++;
	line = malloc(ft_strlen(text) + 1);
	if (!(line))
		return (NULL);
	while (i <= len)
	{
		line[i] = text[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

// reads fd
char	*get_next_line(int fd)
{
	static char	*text;
	char		*line;
	ssize_t		i;

	if (fd == -1 || BUFFER_SIZE < 1)
		return (0);
	line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	i = 1;
	while (is_newline(text) == 0 && (i != 0))
	{	
		i = read(fd, line, BUFFER_SIZE);
		if (i == -1)
		{
			free(line);
			return (NULL);
		}
		line[i] = '\0';
		text = ft_strjoin(text, line);
	}
	free(line);
	line = get_line(text);
	text = new_text(text);
	return (line);
}
