/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:41:57 by heddahbi          #+#    #+#             */
/*   Updated: 2023/12/13 21:42:01 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	re_draw(t_mlx *win)
{
	win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	win->img1 = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	raycast(win);
	render_3d(win);
}
