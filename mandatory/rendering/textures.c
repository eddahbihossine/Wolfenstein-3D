/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:42:07 by heddahbi          #+#    #+#             */
/*   Updated: 2023/12/13 21:42:08 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_texture(t_mlx *win)
{
	if (!win->ptr[0])
	{
		win->ptr[0] = mlx_load_png(win->map->no);
		win->ptr[1] = mlx_load_png(win->map->so);
		win->ptr[2] = mlx_load_png(win->map->we);
		win->ptr[3] = mlx_load_png(win->map->ea);
	}
}

void	get_array_index(t_mlx *win, int i)
{
	int	w;
	int	j;
	int	k;

	j = -1;
	k = -1;
	w = 0;
	win->texture_index = check_whichtexture(win, i);
	win->texture = win->ptr[win->texture_index];
	win->correct_distance = win->ray[i].ray_distance
		* cos(win->map->player->angle - win->ray[i].ray_angle);
	win->wall_strip_heightt = win->projection_distance
		* 64 / win->correct_distance;
	win->y1 = (HEIGHT / 2) - (win->wall_strip_heightt / 2);
	win->y = -1;
	while (++j < 64)
	{
		k = -1;
		while (++k < 64)
		{
			win->s[j][k] = texture_color(win, w);
			w += 4;
		}
	}
}

void	draw_texture(t_mlx *win, int i, int x, int l)
{
	if (win->ray[i].was_hit_vertical)
		x = fmod(win->ray[i].wall_hit_y, 64);
	else
		x = fmod(win->ray[i].wall_hit_xt, 64);
	l = 64 * (win->y - win->y1) / win->wall_strip_heightt;
	mlx_put_pixel(win->img, i, win->y, win->s[l][x]);
}

void	render_3d(t_mlx *win)
{
	int	i;
	int	x;
	int	l;

	init_texture(win);
	x = 0;
	l = 0;
	win->projection_distance = (WIDTH / 2) / tan((60 * (M_PI / 180)) / 2);
	i = -1;
	while (++i < WIDTH)
	{
		get_array_index(win, i);
		while (++win->y < HEIGHT)
		{
			if (win->y < win->y1)
				mlx_put_pixel(win->img, i, win->y, (ceiling_color(win)));
			else if (win->y < win->y1 + win->wall_strip_heightt)
				draw_texture(win, i, x, l);
			else
				mlx_put_pixel(win->img, i, win->y, (floor_color(win)));
		}
	}
	mlx_image_to_window(win->mlx, win->img, 0, 0);
}
