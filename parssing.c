/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:40:30 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/11 20:43:41 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parsing_map(t_map *map, int fd, char *str)
{
	if (init_all(map, fd, str) || check_player_position(map))
		return (1);
	if (update_map(map) || check_wall(map))
		return (1);
	if (get_player_position(map))
		return (1);
	if (check_valid_map(map))
		return (1);
	if (valid_walls(map))
		return (1);
	if (wall_check(map))
		return (1);
	if (valid_position(map))
		return (1);
	if (open_texture(map))
		return (1);
	return (0);
}

void	init__map(t_map *map)
{
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->map = NULL;
	map->map_width = 0;
	map->map_height = 0;
	map->floor.r = -42;
	map->floor.g = 0;
	map->floor.b = 0;
	map->ceiling.r = -42;
	map->ceiling.g = 0;
	map->ceiling.b = 0;
}