/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:38:19 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/11 23:41:06 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	valid_range(int r, int g, int b)
{
	if (r < 0 || r > 255)
		return (1);
	if (g < 0 || g > 255)
		return (1);
	if (b < 0 || b > 255)
		return (1);
	return (0);
}

int	parsing_coma(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (1);
	return (0);
}

int	parsing_floor_ceiling(char **line)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	while (line[i] != NULL)
	{
		j = 0;
		p = ft_strtrim(line[i], "' ' '\t' '\n' '\v' '\f' '\r'");
		while (p[j] != '\0')
		{
			if (!is_digit(p[j]))
				return (free(p), 1);
			j++;
		}
		free(p);
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}

int	init_floor(t_map *map, char *ptr)
{
	char	*tmp;
	char	**split;

	tmp = skip_space(ptr);
	if (parsing_coma(tmp))
		return (free(tmp), 1);
	split = ft_split(tmp, ',');
	if (parsing_floor_ceiling(split))
	{
		ft_free(split);
		free(tmp);
		return (1);
	}
	map->floor.r = ft_atoi(split[0]);
	map->floor.g = ft_atoi(split[1]);
	map->floor.b = ft_atoi(split[2]);
	ft_free(split);
	free(tmp);
	if (valid_range(map->floor.r, map->floor.g, map->floor.b))
		return (1);
	return (0);
}

int	init_ceiling(t_map *map, char *line)
{
	char	*tmp;
	char	**split;
	char	*ptr;

	ptr = ft_substr(line, 1, ft_strlen(line));
	tmp = skip_space(ptr);
	if (parsing_coma(tmp))
		return (free(tmp), free(ptr), 1);
	split = ft_split(tmp, ',');
	if (parsing_floor_ceiling(split))
		return (ft_free(split), free(tmp), free(ptr), 1);
	map->ceiling.r = ft_atoi(split[0]);
	map->ceiling.g = ft_atoi(split[1]);
	map->ceiling.b = ft_atoi(split[2]);
	ft_free(split);
	free(tmp);
	free(ptr);
	if (valid_range(map->ceiling.r, map->ceiling.g, map->ceiling.b))
		return (1);
	return (0);
}
