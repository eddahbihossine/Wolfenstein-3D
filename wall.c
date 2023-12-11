/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:52:00 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/11 20:07:40 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

int	valid_wall_help(t_map *map, int i, int j)
{
	if (i == map->map_height - 1)
	{
		if (map->map[i][j] == '0')
		{
			if (map->map[i][j - 1] == '0')
				return (1);
		}
	}
	if (map->map[i][j] == '0')
	{
		if (map->map[i][j + 1] == '0')
			return (1);
	}
	return (0);
}

int	valid_walls(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i] != NULL)
	{
		j = 0;
		while (map->map[i][j] != '\0')
		{
			if (i == 0 || i == map->map_height - 1)
				if (valid_wall_help(map, i, j))
					return (1);
			if (map->map[i][j] == '0' && i != 0 && i != map->map_height - 1
				&& j != 0 && j != map->map_width - 1)
			{
				if ((map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' '
					|| map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' '))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	front_wall(char *line)
{
	int		i;
	char	*wall;

	i = 0;
	wall = ft_strtrim(line, " ");
	while (wall[i] != '\0')
	{
		while (wall[i] == ' ')
			i++;
		if (wall[i] != '1')
		{
			free(wall);
			return (1);
		}
		i++;
	}
	free(wall);
	return (0);
}

int	back_wall(char *line)
{
	int		i;
	char	*wall;

	i = 0;
	wall = ft_strtrim(line, " ");
	while (wall[i] != '\0')
	{
		while (wall[i] == ' ')
			i++;
		if (wall[i] != '1')
		{
			free(wall);
			return (1);
		}
		i++;
	}
	free(wall);
	return (0);
}

int	wall_check(t_map *map)
{
	int		i;
	char	*wall;

	i = 0;
	if (map == NULL || map->map == NULL || map->map[0] == NULL)
		return (1);
	if (front_wall(map->map[0]))
		return (1);
	i = 1;
	while (map->map[i] != NULL)
	{
		if (map->map[i + 1] == NULL)
			break ;
		wall = ft_strtrim(map->map[i], " ");
		if (wall[0] != '1' || wall[ft_strlen(wall) - 1] != '1')
		{
			free(wall);
			return (1);
		}
		free(wall);
		i++;
	}
	if (back_wall(map->map[i]))
		return (1);
	return (0);
}
