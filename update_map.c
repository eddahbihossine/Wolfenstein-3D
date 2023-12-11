/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:36:31 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/11 19:50:17 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

int	check_wall(t_map *map)
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
			if (map->map[i][j] == '2')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	init_widht_height(t_map *map)
{
	map->map_width = get_longest_line(map);
	map->map_height = get_height(map);
}

char	get_char(t_map *map, int i, int j)
{
	if (map->map[i][j])
	{
		if (map->map[i][j] != '1' && map->map[i][j] != '0'
			&& map->map[i][j] != 'N' && map->map[i][j] != 'S'
				&& map->map[i][j] != 'W' && map->map[i][j] != 'E'
					&& map->map[i][j] != ' ')
			return ('2');
		else
			return (map->map[i][j]);
	}
	else
		return ('\0');
	return ('\0');
}

void	update(t_map *map, int i, char *tmp)
{
	free(map->map[i]);
	map->map[i] = tmp;
}

int	update_map(t_map *map)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	init_widht_height(map);
	while (i < map->map_height)
	{
		j = -1;
		tmp = malloc(sizeof(char) * (map->map_width + 1));
		while (++j < map->map_width)
		{
			if ((size_t)j < ft_strlen(map->map[i]))
				tmp[j] = get_char(map, i, j);
			else
				tmp[j] = ' ';
		}
		tmp[j] = '\0';
		update(map, i, tmp);
		i++;
	}
	free_empty_line(map, &i);
	return (0);
}
