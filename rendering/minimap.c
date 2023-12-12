#include "../includes/cub3D.h"

void	re_draw(t_mlx *win)
{
	win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	win->img1 = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	raycast(win);
	render_3d(win);
	adraw(win);
}

int	mlx_draw(t_mlx *win, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 20)
	{
		j = 0;
		while (j < 20)
		{
			mlx_put_pixel(win->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
	return (0);
}

void	draw_minimap(t_mlx *win)
{
	if (win->map_2d.x > 9 && win->map_2d.y > 9)
	{
		if (has_wall(win, win->map_2d.x, win->map_2d.y))
			mlx_put_pixel(win->img, win->map_2d.ymin,
				win->map_2d.xmin, 0xFFF34675);
		else
			mlx_put_pixel(win->img, win->map_2d.ymin,
				win->map_2d.xmin, 0x0DEADBF);
	}
	else
		mlx_put_pixel(win->img, win->map_2d.ymin,
			win->map_2d.xmin, 0x000000000);
	win->map_2d.x++;
	win->map_2d.xmin++;
}

void	adraw(t_mlx *win)
{
	win->map_2d.y = (int)win->map->player->y - 100;
	win->map_2d.ymin = 9;
	while (win->map_2d.ymin < 200)
	{
		win->map_2d.x = (int)win->map->player->x - 100;
		win->map_2d.xmin = 9;
		while (win->map_2d.xmin < 200)
			draw_minimap(win);
		win->map_2d.y++;
		win->map_2d.ymin++;
	}
	win->map_2d.ymin = 9;
	while (win->map_2d.ymin < 14)
	{
		win->map_2d.xmin = 9;
		while (win->map_2d.xmin < 14)
		{
			mlx_put_pixel(win->img, win->map_2d.xmin + 100,
				win->map_2d.ymin + 100, 0x000000000);
			win->map_2d.xmin++;
		}
		win->map_2d.ymin++;
	}
	mlx_image_to_window(win->mlx, win->img, 0, 0);
}
