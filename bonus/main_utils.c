/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:22:38 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/12 22:34:47 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

void	ft_free_window(t_mlx **window)
{
	ft_free_map(&(*window)->map);
	free((*window));
}

void	_close_win(void *param)
{
	(void)param;
	exit(0);
}

void	mlx(t_mlx *window)
{
	window->mlx = mlx_init(WIDTH, HEIGHT, "./includes/cub3D", false);
	window->img = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	init_params(window);
	mlx_image_to_window(window->mlx, window->img, 0, 0);
	mlx_loop_hook(window->mlx, hook_stuff, window);
	render_3d(window);
	mlx_close_hook(window->mlx, _close_win, window);
	mlx_loop(window->mlx);
}

int	check_map(int ac, char **av)
{
	if (ac != 2 || (check_file(av[1]) == 0))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}

int	init_mlx(t_mlx *window, int fd, char **av)
{
	window->map = malloc(sizeof(t_map));
	if (!window->map)
		return (free (window), 1);
	window->map->player = malloc(sizeof(t_player));
	if (!window->map)
		return (free (window->map), free(window), 1);
	init__map(window->map);
	if (parsing_map(window->map, fd, av[1]))
	{
		write(2, "Error\n", 6);
		ft_free_window(&window);
		free(window->map->player);
		close(fd);
		return (1);
	}
	return (0);
}
