/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:19:58 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/11 23:53:53 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	get_map(t_map *map, int *k, int *i, char *line)
{
	if (*k == 6)
	{
		map->map[*i] = my_strdup(line);
		*i += 1;
	}
}

int	get_ceiling(char *line, int *k, t_map *map)
{
	char	*ptr;

	ptr = ft_substr(line, 1, size_line(line) -1);
	if (init_ceiling(map, ptr))
	{
		free(ptr);
		return (1);
	}
	free(ptr);
	*k += 1;
	return (0);
}

void	all_texture(t_map *map, char *line, int *k)
{
	line = skip_space(line);
	if (line[0] == 'N' && line[1] == 'O' && !map->no)
		get_north_texture(line, k, map);
	else if (line[0] == 'S' && line[1] == 'O' && !map->so)
		get_south_texture(line, k, map);
	else if (line[0] == 'W' && line[1] == 'E' && !map->we)
		get_west_texture(line, k, map);
	else if (line[0] == 'E' && line[1] == 'A' && !map->ea)
		get_east_texture(line, k, map);
	else if (line[0] == 'F' && map->floor.r == -42)
		get_floor(line, k, map);
	else if (line[0] == 'C' && map->ceiling.r == -42)
		get_ceiling(line, k, map);
	free(line);
}

int	valid_line(t_map *map, int fd, int k, int i)
{
	map->map[i] = NULL;
	close(fd);
	if (k != 6)
		return (1);
	return (0);
}

int	init_all(t_map *map, int fd, char *str)
{
	char	*line;
	int		i;
	int		count;
	int		k;

	count = 0;
	i = 0;
	k = 0;
	init_map(map, count_lines(str));
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (check_empty_line(line, map))
		{
			line = get_next_line(fd);
			continue ;
		}
		if (count < 6)
			all_texture(map, line, &k);
		else
			get_map(map, &k, &i, line);
		free(line);
		line = next_line(&count, line, fd);
	}
	return (valid_line(map, fd, k, i));
}
