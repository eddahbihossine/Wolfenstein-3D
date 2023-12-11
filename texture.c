/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:06:40 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/11 18:16:03 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_north_texture(char *line, int *k, t_map *map)
{
	char	*ptr;

	ptr = ft_substr(line, 2, size_line(line) -2);
	map->no = skip_space(ptr);
	free(ptr);
	*k += 1;
	return (0);
}

int	get_south_texture(char *line, int *k, t_map *map)
{
	char	*ptr;

	ptr = ft_substr(line, 2, size_line(line) -2);
	map->so = skip_space(ptr);
	free(ptr);
	*k += 1;
	return (0);
}

int	get_west_texture(char *line, int *k, t_map *map)
{
	char	*ptr;

	ptr = ft_substr(line, 2, size_line(line) -2);
	map->we = skip_space(ptr);
	free(ptr);
	*k += 1;
	return (0);
}

int	get_east_texture(char *line, int *k, t_map *map)
{
	char	*ptr;

	ptr = ft_substr(line, 2, size_line(line) -2);
	map->ea = skip_space(ptr);
	free(ptr);
	*k += 1;
	return (0);
}

int	get_floor(char *line, int *k, t_map *map)
{
	char	*ptr;

	ptr = ft_substr(line, 1, size_line(line) -1);
	if (init_floor(map, ptr))
	{
		free(ptr);
		return (1);
	}
	free(ptr);
	*k += 1;
	return (0);
}
