/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:26:00 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/11 20:39:31 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_file(char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (file[i] == '.')
		{
			if (file[i + 1] == 'c' && file[i + 2] == 'u' && file[i + 3] == 'b')
				return (1);
		}
		i++;
	}
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

char	*skip_space(char *line)
{
	int		i;
	char	*ptr;

	i = 0;
	while (is_space(line[i]))
		i++;
	ptr = ft_substr(line, i, ft_strlen(line) - i);
	return (ptr);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	open_texture(t_map *map)
{
	int	no;
	int	so;
	int	we;
	int	ea;

	no = open(map->no, O_RDONLY);
	if (no == -1)
		return (1);
	so = open(map->so, O_RDONLY);
	if (so == -1)
		return (close(no), 1);
	we = open(map->we, O_RDONLY);
	if (we == -1)
		return (close(no), close(so), 1);
	ea = open(map->ea, O_RDONLY);
	if (ea == -1)
		return (close(no), close(so), close(we), 1);
	return (close(no), close(so), close(we), close(ea), 0);
}
