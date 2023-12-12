/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:48:05 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/12 03:55:04 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	radians_to_degrees(double radians)
{
	return (radians * (180.0 / M_PI));
}

double	degrees_to_radians(double degrees)
{
	return (degrees * (M_PI / 180));
}

int	check_wall_collision(t_mlx *win, double xx, double yy)
{
	int	x;
	int	y;

	x = floor(xx / 64);
	y = floor(yy / 64);
	if (win->ray[0].ray_distance < 12 && win->ray[799].ray_distance < 12)
	{
		if (win->ray[0].ray_distance < win->ray[799 / 2].ray_distance
			&& win->ray[799].ray_distance < win->ray[799 / 2].ray_distance)
			return (6);
	}
	if (x < 0 || y < 0 || x > win->map->map_width || y > win->map->map_height)
		return (1);
	return (win->map->map[y][x] == '1');
}

void	hook_stuff(void *params)
{
	t_mlx	*win;

	win = (t_mlx *)params;
	mlx_delete_image(win->mlx, win->img);
	mlx_delete_image(win->mlx, win->img1);
	if (mlx_is_key_down(win->mlx, ESC))
		exit(0);
	if (mlx_is_key_down(win->mlx, W))
		moveforward(win, 5);
	else if (mlx_is_key_down(win->mlx, S))
		movebackward(win, 5);
	else if (mlx_is_key_down(win->mlx, A))
		moveleft(win, 5);
	else if (mlx_is_key_down(win->mlx, D))
		moveright(win, 5);
	else if (mlx_is_key_down(win->mlx, LEFT))
		win->map->player->angle -= 0.04;
	else if (mlx_is_key_down(win->mlx, RIGHT))
		win->map->player->angle += 0.04;
	else if (mlx_is_mouse_down(win->mlx, 0))
		win->map->player->angle += 0.04;
	else if (mlx_is_mouse_down(win->mlx, 1))
		win->map->player->angle -= 0.04;
	
	re_draw(win);
}
