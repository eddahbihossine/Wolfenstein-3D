/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 22:41:30 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/11 01:24:19 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_get_line(char **str, char **line, int new_line)
{
	*line = ft_substr(*str, 0, new_line + 1);
	*str = get_rest(str, new_line + 1);
	return (*line);
}

char	*get_rest(char **str, int new_line)
{
	char	*rest;
	int		len;

	len = ft_strlen(*str + new_line);
	rest = ft_substr(*str, new_line, len);
	free(*str);
	*str = NULL;
	return (rest);
}

int	ft_check_new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buff;
	char		*line;
	int			reader;
	int			new_line;

	if (!str)
		str = ft_strdup("");
		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		reader = read(fd, buff, BUFFER_SIZE);
	while (reader >= 0)
	{
		buff[reader] = '\0';
		if ((!str[0] && !reader))
			break ;
		str = ft_strjoin(str, buff);
		new_line = ft_check_new_line(str);
		if (new_line != -1)
			return (free(buff), ft_get_line(&str, &line, new_line));
		if (!reader)
			return (free(buff), get_rest(&str, 0));
		reader = read(fd, buff, BUFFER_SIZE);
	}
	return (free(str), free(buff), str = NULL, NULL);
}
