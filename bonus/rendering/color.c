/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:40:41 by heddahbi          #+#    #+#             */
/*   Updated: 2023/12/13 21:40:42 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

size_t	floor_color(t_mlx *win)
{
	size_t	floor;

	floor = get_color(win->map->floor.r, win->map->floor.g,
			win->map->floor.b, 255);
	return (floor);
}

size_t	ceiling_color(t_mlx *win)
{
	size_t	ceiling;

	ceiling = get_color(win->map->ceiling.r, win->map->ceiling.g,
			win->map->ceiling.b, 255);
	return (ceiling);
}

size_t	texture_color(t_mlx *win, int w)
{
	size_t	texture;

	texture = get_color(win->texture->pixels[w],
			win->texture->pixels[w + 1], win->texture->pixels[w + 2],
			win->texture->pixels[w + 3]);
	return (texture);
}

int	check_whichtexture(t_mlx *win, int i)
{
	if (win->ray[i].was_hit_vertical)
	{
		if (check_leftorrigh(win->ray[i].ray_angle))
			return (0);
		else
			return (1);
	}
	else
	{
		if (check_upordown(win->ray[i].ray_angle))
			return (2);
		else
			return (3);
	}
	return (-1);
}

size_t	get_color(int r, int g, int b, int a)
{
	return (((r & 255) << 24) + ((g & 255) << 16)
		+ ((b & 255) << 8) + (a & 255));
}
