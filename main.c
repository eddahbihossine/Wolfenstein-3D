
#include "./includes/cub3D.h"

void f()
{
    system("leaks cub3D");
}

void	ft_free_window(t_mlx **window)
{
	ft_free_map(&(*window)->map);
	free((*window));
}

void _close_win(void * param)
{
    (void)param;
    exit(0);
}



int main(int ac, char **av) 
{
    int fd;
    atexit(f);
    
    if (ac != 2 || check_file(av[1]) == 0) 
    {
        printf("Error\n");
        return (1);
    }
    fd = open(av[1], O_RDONLY);
    if (fd == -1) 
    {
        printf("Error opening file\n");
        return 1;
    }
    
    t_mlx *window = malloc(sizeof(t_mlx));
    if(!window)
        return (1);
    window->map = malloc(sizeof(t_map));
    window->map->player = malloc(sizeof(t_player));
    if(!window->map)
        return (1);
    init__map(window->map);
    if (parsing_map(window->map, fd, av[1]))
    {
        printf("Error\n");
        ft_free_window(&window);
        free(window->map->player);
        return (1);
    }

    window->mlx = mlx_init(WIDTH, HEIGHT, "./includes/cub3D",false);
    window->img = mlx_new_image(window->mlx, WIDTH, HEIGHT);
    window->img1 = mlx_new_image(window->mlx, 22,22);
    init_params(window);
    mlx_image_to_window(window->mlx, window->img, 0, 0);
    mlx_image_to_window(window->mlx, window->img1, 0, 0);
    mlx_loop_hook(window->mlx, hook_stuff, window);
    render_3d(window);
    adraw(window);
    mlx_close_hook(window->mlx, _close_win, window);
    mlx_loop(window->mlx);
    ft_free_window(&window);
    free(window->map->player);
    close(fd);
    return 0;
}

