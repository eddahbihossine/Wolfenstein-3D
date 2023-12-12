/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycast_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:26:11 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/12 21:26:12 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	normalize_angle(double *angle)
{
	*angle = remainder(*angle, 2 * M_PI);
	if (*angle < 0)
		*angle = (2 * M_PI) + *angle;
	return (*angle);
}

void	raycast(t_mlx *win)
{
	int		i;
	double	ray_angle;
	double	horizray_distance;
	double	verray_distance;
	double	ray_step;

	i = 0;
	ray_angle = win->map->player->angle - ((60 * (M_PI / 180)) / 2);
	ray_step = (60 * (M_PI / 180)) / WIDTH;
	while (i < WIDTH)
	{
		win->ray[i].ray_angle = normalize_angle(&ray_angle);
		horizray_distance = horizget_the_distance(win,
				win->ray[i].ray_angle, i);
		verray_distance = vertget_the_distance(win,
				win->ray[i].ray_angle, i);
		win->ray[i].ray_distance = compare_distance(horizray_distance,
				verray_distance, win, i);
		ray_angle += ray_step;
		i++;
	}
}
