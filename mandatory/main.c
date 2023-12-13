/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:15:29 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/13 21:42:24 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

int	main(int ac, char **av)
{
	int		fd;
	t_mlx	*window;

	if (check_map(ac, av))
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	window = malloc(sizeof(t_mlx));
	if (!window)
		return (1);
	if (init_mlx(window, fd, av))
		return (1);
	mlx(window);
	ft_free_window(&window);
	free(window->map->player);
	close(fd);
	return (0);
}
