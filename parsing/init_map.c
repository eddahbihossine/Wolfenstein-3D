/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:51:35 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/11 23:53:51 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	count_lines(char *str)
{
	int		count;
	char	*line;
	int		fd;

	count = 0;
	fd = open(str, O_RDONLY);
	line = get_next_line(fd);
	while ((line != NULL))
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

void	init_map(t_map *map, int size)
{
	int	i;

	i = 0;
	map->map = malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		map->map[i] = NULL;
		i++;
	}
}

int	get_width(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '1')
			count++;
		i++;
	}
	return (count);
}

int	get_height(t_map *map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (map->map[i] != NULL)
	{
		count++;
		i++;
	}
	while (ft_strncmp(map->map[i - 1], "\0", 1) == 0)
	{
		i--;
		count--;
	}
	return (count);
}

int	size_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	return (i);
}
