/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:41:47 by heddahbi          #+#    #+#             */
/*   Updated: 2023/12/13 21:41:48 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_intersection(t_mlx *win, int x, int y)
{
	int	i;
	int	j;

	if (x < 0 || x > win->map->map_width || y < 0
		|| y > win->map->map_height)
		return (1);
	i = floor(y);
	j = floor(x);
	if (i >= win->map->map_height || j >= win->map->map_width)
		return (1);
	return (win->map->map[i][j] == '1');
}

int	check_upordown(double ray_angle)
{
	if (ray_angle > 0 && ray_angle < M_PI)
		return (1);
	return (0);
}

int	check_leftorrigh( double ray_angle)
{
	if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
		return (1);
	return (0);
}

int	has_wall(t_mlx *win, double x, double y)
{
	int	i;
	int	j;

	if (x < 0 || y < 0 || x > win->map->map_width * 64
		|| y > win->map->map_height * 64)
		return (1);
	i = floor(y / 64);
	j = floor(x / 64);
	if (i >= win->map->map_height || j >= win->map->map_width)
		return (1);
	return (win->map->map[i][j] == '1');
}

double	ft_sqrt1(t_mlx *win, int xinter, int yinter, int i)
{
	win->ray[i].wall_hit_x = xinter;
	win->ray[i].wall_hit_y = yinter;
	return (sqrt(pow(win->map->player->x - xinter, 2)
			+ pow(win->map->player->y - yinter, 2)));
}
