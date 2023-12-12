/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:13:49 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/11 23:53:44 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	*next_line(int *cout, char *line, int fd)
{
	line = get_next_line(fd);
	*cout = *cout + 1;
	return (line);
}

void	ft_free_map(t_map **map)
{
	int	i;

	i = 0;
	if ((*map)->no)
		free((*map)->no);
	if ((*map)->so)
		free((*map)->so);
	if ((*map)->we)
		free((*map)->we);
	if ((*map)->ea)
		free((*map)->ea);
	while ((*map)->map[i] != NULL)
	{
		free((*map)->map[i]);
		i++;
	}
	if ((*map)->map)
		free((*map)->map);
	free(*map);
}

void	free_empty_line(t_map *map, int *i)
{
	while (map->map[*i] != NULL)
	{
		free(map->map[*i]);
		map->map[*i] = NULL;
		*i += 1;
	}
}
