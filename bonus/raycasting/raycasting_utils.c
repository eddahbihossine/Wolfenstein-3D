/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:40:26 by heddahbi          #+#    #+#             */
/*   Updated: 2023/12/13 21:40:27 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_whichside(t_mlx *win)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (win->map->map[i] != NULL)
	{
		j = 0;
		while (win->map->map[i][j] != '\0')
		{
			if (win->map->map[i][j] == 'N')
				return (1);
			if (win->map->map[i][j] == 'S')
				return (2);
			if (win->map->map[i][j] == 'W')
				return (3);
			if (win->map->map[i][j] == 'E')
				return (4);
			j++;
		}
		i++;
	}
	return (0);
}

void	set_the_vision_angle(t_mlx *win, int side)
{
	if (side == 1)
		win->map->player->angle = M_PI_2;
	else if (side == 2)
		win->map->player->angle = 3 * M_PI_2;
	else if (side == 3)
		win->map->player->angle = M_PI;
	else if (side == 4)
		win->map->player->angle = 0;
}

void	init_params(t_mlx *win)
{
	win->map->player->fov = degrees_to_radians(60);
	win->map->player->number_rays = WIDTH;
	set_the_vision_angle(win, check_whichside(win));
}

double	compare_distance(double a, double b, t_mlx *win, int i)
{
	win->ray[i].was_hit_vertical = 0;
	if (a > b)
	{
		win->ray[i].was_hit_vertical = 1;
		return (b);
	}
	return (a);
}
