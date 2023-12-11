/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:18:08 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/11 19:31:13 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_player_position(t_map *map)
{
	int		i;
	int		j;
	int		count;
	t_map	*tmp;

	tmp = map;
	i = 0;
	count = 0;
	j = 0;
	while (tmp->map[i] != NULL)
	{
		j = 0;
		while (tmp->map[i][j] != '\0')
		{
			if (tmp->map[i][j] == 'N' || tmp->map[i][j] == 'S'
				|| tmp->map[i][j] == 'W' || tmp->map[i][j] == 'E')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		return (1);
	return (0);
}

int	valid_position(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map[i] != NULL)
	{
		j = 0;
		while (map->map[i][j] != '\0')
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'W' || map->map[i][j] == 'E')
			{
				if (map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' '
					|| map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' ')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_valid_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->map[i] != NULL)
	{
		j = 0;
		if (strcmp(map->map[i], "\0") == 0)
			return (1);
		while (map->map[i][j] != '\0')
		{
			if (map->map[i][j] != '1' && map->map[i][j] != '0'
				&& map->map[i][j] != 'N'
					&& map->map[i][j] != 'S' && map->map[i][j] != 'W'
						&& map->map[i][j] != 'E' && map->map[i][j] != ' ')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	get_longest_line(t_map *map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = 0;
	j = 0;
	while (map->map[i] != NULL)
	{
		j = 0;
		while (map->map[i][j] != '\0')
		{
			j++;
		}
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}