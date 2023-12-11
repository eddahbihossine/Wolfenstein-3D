/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:08:04 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/11 19:08:28 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*my_strdup(char *line)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (size_line(line) + 1));
	while (line[i] != '\0' && line[i] != '\n')
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	is_empty(char *line)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (is_space(line[i]))
			count++;
		i++;
	}
	if (count == (ft_strlen(line)))
		return (1);
	return (0);
}

int	check_empty_line(char *line, t_map *map)
{
	if (is_empty(line) == 1 && map->map[0] == NULL)
	{
		free(line);
		return (1);
	}
	return (0);
}
