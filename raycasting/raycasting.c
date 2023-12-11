/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 23:37:48 by heddahbi          #+#    #+#             */
/*   Updated: 2023/12/11 23:37:49 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3D.h"

double	ft_sqrt(t_mlx *win, int x, int y, int i)
{
	win->ray[i].wall_hit_xt = x;
	win->ray[i].wall_hit_yt = y;
	return (sqrt(pow(win->map->player->x - x, 2)
			+ pow(win->map->player->y - y, 2)));
}

double	x_step_checker(double ray_angle, double x_step)
{
	double	n_x;

	if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2 && x_step > 0)
		x_step *= -1;
	if ((ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2) && x_step < 0)
		x_step *= -1;
	n_x = x_step;
	return (n_x);
}

double	y_step_checker(double ray_angle, double ystep)
{
	double	n_y;

	if (ray_angle > M_PI && ystep > 0)
		ystep *= -1;
	if (ray_angle < M_PI && ystep < 0)
		ystep *= -1;
	n_y = ystep;
	return (n_y);
}

double	horizget_the_distance(t_mlx *win, double ray_angle, int i)
{
	double	x;
	double	y;
	double	xstep;
	double	ystep;

	y = floor(win->map->player->y / 64) * 64;
	if (ray_angle > 0 && ray_angle < M_PI)
		y += 64;
	x = win->map->player->x + ((y - win->map->player->y) / tan(ray_angle));
	ystep = 64;
	if (ray_angle > M_PI)
		ystep *= -1;
	xstep = 64 / tan(ray_angle);
	xstep = x_step_checker(ray_angle, xstep);
	if (ray_angle > M_PI)
		y -= 0.1;
	while (!has_wall(win, x, y))
	{
		x += xstep;
		y += ystep;
	}
	return (ft_sqrt(win, x, y, i));
}

double	vertget_the_distance(t_mlx *win, double ray_angle, int i)
{
	double	xinter;
	double	yinter;
	double	xstep;
	double	ystep;

	xinter = floor(win->map->player->x / 64) * 64;
	if (ray_angle > 3 * M_PI / 2 || ray_angle < M_PI / 2)
		xinter += 64;
	yinter = win->map->player->y + ((xinter - win->map->player->x)
			* tan(ray_angle));
	xstep = 64;
	if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
		xstep *= -1;
	ystep = 64 * tan(ray_angle);
	ystep = y_step_checker(ray_angle, ystep);
	if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
		xinter -= 0.1;
	while (!has_wall(win, xinter, yinter))
	{
		xinter += xstep;
		yinter += ystep;
	}
	win->ray[i].wall_hit_x = xinter;
	win->ray[i].wall_hit_y = yinter;
	return (sqrt(pow(win->map->player->x - xinter, 2)
			+ pow(win->map->player->y - yinter, 2)));
}
