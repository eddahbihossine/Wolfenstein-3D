/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:39:56 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/11 21:47:25 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	moveforward(t_mlx *mlx, double speed)
{
	if (check_wall_collision(mlx, mlx->map->player->x
			+ cos(mlx->map->player->angle)
			* speed, mlx->map->player->y
			+ cos(mlx->map->player->angle) * speed) == 6)
		return ;
	if (check_wall_collision(mlx, mlx->map->player->x, mlx->map->player->y)
		|| check_wall_collision(mlx, mlx->map->player->x
			+ cos(mlx->map->player->angle)
			* speed, mlx->map->player->y
			+ sin(mlx->map->player->angle) * speed))
		return ;
	mlx->map->player->x += cos(mlx->map->player->angle) * speed;
	mlx->map->player->y += sin(mlx->map->player->angle) * speed;
}

void	movebackward(t_mlx *mlx, double speed)
{
	if (check_wall_collision(mlx, mlx->map->player->x
			+ cos(mlx->map->player->angle)
			* speed, mlx->map->player->y
			+ cos(mlx->map->player->angle) * speed) == 6)
		return ;
	if (check_wall_collision(mlx, mlx->map->player->x, mlx->map->player->y)
		|| check_wall_collision(mlx, mlx->map->player->x
			- cos(mlx->map->player->angle)
			* speed, mlx->map->player->y
			- sin(mlx->map->player->angle) * speed))
		return ;
	mlx->map->player->x -= cos(mlx->map->player->angle) * speed;
	mlx->map->player->y -= sin(mlx->map->player->angle) * speed;
}

void	moveleft(t_mlx *mlx, double speed)
{
	if (check_wall_collision(mlx, mlx->map->player->x
			+ cos(mlx->map->player->angle)
			* speed, mlx->map->player->y
			+ cos(mlx->map->player->angle) * speed) == 6)
		return ;
	if (check_wall_collision(mlx, mlx->map->player->x, mlx->map->player->y)
		|| check_wall_collision(mlx, mlx->map->player->x
			+ cos(mlx->map->player->angle - M_PI_2)
			* speed, mlx->map->player->y
			+ sin(mlx->map->player->angle - M_PI_2) * speed))
		return ;
	mlx->map->player->x += cos(mlx->map->player->angle - M_PI_2) * speed;
	mlx->map->player->y += sin(mlx->map->player->angle - M_PI_2) * speed;
}

void	moveright(t_mlx *mlx, double speed)
{
	if (check_wall_collision(mlx, mlx->map->player->x
			+ cos(mlx->map->player->angle)
			* speed, mlx->map->player->y
			+ cos(mlx->map->player->angle) * speed) == 6)
		return ;
	if (check_wall_collision(mlx, mlx->map->player->x, mlx->map->player->y)
		|| check_wall_collision(mlx, mlx->map->player->x
			+ cos(mlx->map->player->angle + M_PI_2)
			* speed, mlx->map->player->y
			+ sin(mlx->map->player->angle + M_PI_2) * speed))
		return ;
	mlx->map->player->x += cos(mlx->map->player->angle + M_PI_2) * speed;
	mlx->map->player->y += sin(mlx->map->player->angle + M_PI_2) * speed;
}
