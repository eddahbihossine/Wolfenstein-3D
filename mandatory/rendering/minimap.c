#include "../includes/cub3D.h"

void	re_draw(t_mlx *win)
{
	win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	win->img1 = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	raycast(win);
	render_3d(win);
}

