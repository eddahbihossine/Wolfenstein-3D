#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub3D.h"






void	render_3d(t_mlx *win);
void	adraw(t_mlx *win);
int	has_wall(t_mlx *win, double x, double y);


void f()
{
    system("leaks cub3D");
}


void raycast(t_mlx *win);

void	ft_free_window(t_mlx **window)
{
	ft_free_map(&(*window)->map);
	free((*window));
}

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

int	xray_direction(double ray_angle)
{
	return (fabs(cos(ray_angle)) / cos(ray_angle));
}

int	yray_direction(double ray_angle)
{
	return (fabs(sin(ray_angle)) / sin(ray_angle));
}

int	check_intersection(t_mlx *win, int x, int y)
{
	int	i;
	int	j;

	if (x < 0 || x > win->map->map_width || y < 0
		|| y > win->map->map_height)
		return (1);
	i = floor(y);
	j = floor(x);
	if (i >= win->map->map_height || j >= win->map->map_width)
		return (1);
	return (win->map->map[i][j] == '1');
}

int	check_upordown(double ray_angle)
{
	if (ray_angle > 0 && ray_angle < M_PI)
		return (1);
	return (0);
}

int	check_leftorrigh( double ray_angle)
{
	if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
		return (1);
	return (0);
}

int	has_wall(t_mlx *win, double x, double y)
{
	int	i;
	int	j;

	if (x < 0 || y < 0 || x > win->map->map_width * 64
		|| y > win->map->map_height * 64)
		return (1);
	i = floor(y / 64);
	j = floor(x / 64);
	if (i >= win->map->map_height || j >= win->map->map_width)
		return (1);
	return (win->map->map[i][j] == '1');
}

double	ft_sqrt(t_mlx *win ,int x , int y, int i)
{
	win->ray[i].wall_hit_xt = x;
	win->ray[i].wall_hit_yt = y;
	return (sqrt(pow(win->map->player->x - x, 2)
			+ pow(win->map->player->y - y, 2)));
}
double	horizget_the_distance(t_mlx *win, double ray_angle, int i)
{
	double	x;
	double	y;
	double	xstep;
	double	ystep;

	y = floor(win->map->player->y / 64) * 64;
	if (ray_angle > 0 && ray_angle < M_PI)
		y += 64;
	x = win->map->player->x + ((y - win->map->player->y) / tan(ray_angle));
	ystep = 64;
	if (ray_angle > M_PI)
		ystep *= -1;
	xstep = 64 / tan(ray_angle);
	if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2 && xstep > 0)
		xstep *= -1;
	if ((ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2) && xstep < 0)
		xstep *= -1;
	if (ray_angle > M_PI)
		y -= 0.1;
	while (!has_wall(win, x, y))
	{
		x += xstep;
		y += ystep;
	}
	return (ft_sqrt(win, x, y, i));
}



double vertget_the_distance(t_mlx *win, double ray_angle , int i)
{
	double	xintercept;
	double	yintercept;

	xintercept = floor(win->map->player->x / 64) * 64;
	if (ray_angle > 3 * M_PI / 2 || ray_angle < M_PI / 2)
		xintercept += 64;
	yintercept = win->map->player->y + ((xintercept - win->map->player->x)
			* tan(ray_angle));
	double	xstep;
	double	ystep;
	xstep = 64;
	if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
		xstep *= -1;
	ystep = 64 * tan(ray_angle);
	if (ray_angle > M_PI && ystep > 0)
	    ystep *= -1;
	if (ray_angle < M_PI && ystep < 0)
		ystep *= -1;
	if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
		xintercept -= 0.1;
	while (!has_wall(win, xintercept, yintercept))
	{

		xintercept += xstep;
		yintercept += ystep;
	}
    win->ray[i].wall_hit_x = xintercept;
    win->ray[i].wall_hit_y = yintercept;
    return (sqrt(pow(win->map->player->x - xintercept, 2) + pow(win->map->player->y - yintercept, 2)));
}



double compare_distance(double a , double b, t_mlx *win ,int i)
{
    win->ray[i].was_hit_vertical = 0;
    if(a > b)
    {
        win->ray[i].was_hit_vertical = 1;
        return (b);
    }
    return (a);
    
}

uint8_t *  convert_to_rgb(uint8_t *pixels)
{
    int i = 0;
    int len = ft_strlen((char *)pixels);
    uint8_t *rgb = malloc(sizeof(uint8_t) * len);
    while(i < len)
    {
        rgb[i] = pixels[i];
        i++;
    }
    return (rgb);
}
size_t get_color(int r, int g, int b, int a)
{   
    return ((r & 255) << 24) + ((g & 255) << 16) + ((b & 255) << 8)
           + (a & 255);
}
int check_whichtexture(t_mlx *win,int i) {

    if(win->ray[i].was_hit_vertical)
    {
        if(check_leftorrigh(win->ray[i].ray_angle))
            return (0);
        else
            return (1);
    }
    else
    {
        if(check_upordown(win->ray[i].ray_angle))
            return (2);
        else
            return (3);
    }
   
    
    return (-1);
}
void render_3d(t_mlx *win)
{

	double	correct_distance;
	double	projection_distance;
	int		i = 0;
    mlx_texture_t **ptr;

    ptr = malloc(sizeof(mlx_texture_t *) * 4);

    for (int i = 0; i < 4; i++)
    {
        ptr[i] = malloc(sizeof(mlx_texture_t));
    }
        ptr[0] = mlx_load_png(win->map->no);
        ptr[1] = mlx_load_png(win->map->so);
        ptr[2] = mlx_load_png(win->map->we);
        ptr[3] = mlx_load_png(win->map->ea);
        int **s;

	projection_distance = (WIDTH / 2) / tan((60 * (M_PI / 180)) / 2);
	i = -1;
	while (++i < 800)
	{
        int texture_index = check_whichtexture(win, i);
        win->texture = ptr[texture_index];
        correct_distance = win->ray[i].ray_distance * cos(win->map->player->angle - win->ray[i].ray_angle);
        double wall_strip_heightt = projection_distance * 64 / correct_distance;
        int	y;
        int	y1;
        y1 = (HEIGHT / 2) - (wall_strip_heightt / 2);
        y = -1;
        size_t floor = get_color( win->map->floor.r, win->map->floor.g, win->map->floor.b , 255);
        size_t ceiling = get_color( win->map->ceiling.r, win->map->ceiling.g, win->map->ceiling.b, 255);
            s = malloc(sizeof(int *) * 64 );
            int w = 0;
            for(int j = 0; j < 64; j++)
            {
                s[j] = malloc(sizeof(int) * 64 );
                
                for(int k = 0; k < 64; k++)
                {
                    s[j][k] = get_color(win->texture->pixels[w], win->texture->pixels[w + 1], win->texture->pixels[w + 2], win->texture->pixels[w + 3]);
                    w += 4;
                }
            }
	while (++y < HEIGHT)
	{
		if (y < y1)
			mlx_put_pixel(win->img, i, y, ceiling);
		else if (y < y1 + wall_strip_heightt)
        { 
            int x;
            int l;
            if(win->ray[i].was_hit_vertical)
            {
                x = fmod(win->ray[i].wall_hit_y, 64);
            }
            else
            {
                x = fmod(win->ray[i].wall_hit_xt, 64);
            }
            l = 64 * (y - y1) / wall_strip_heightt;
            mlx_put_pixel(win->img, i, y, s[l][x]);
        }
    
		else
			mlx_put_pixel(win->img, i, y, (u_int32_t)floor);
	}
    }
    int j = 0;
    while(j < 4)
    {
        free(ptr[j]);
        j++;
    }
    free(ptr);
    int k = 0;
    while(k < 64)
    {
        free(s[k]);
        k++;
    }
    free(s);

    mlx_image_to_window(win->mlx, win->img, 0, 0);
}

double normalize_angle(double *angle)
{
    *angle = remainder(*angle, 2 * M_PI);
    if (*angle < 0)
        *angle = (2 * M_PI) + *angle;
    return(*angle);
}

   
void raycast(t_mlx *win)
{
    int i =0;
    double ray_angle =  win->map->player->angle - ((60 * (M_PI / 180)) / 2);
    double horizray_distance;
    double verray_distance;
    double ray_step;
    ray_step = (60 * (M_PI / 180)) / WIDTH;
    while(i < WIDTH)
    {
        win->ray[i].ray_angle = normalize_angle(&ray_angle);
        horizray_distance = horizget_the_distance(win, win->ray[i].ray_angle, i);
        verray_distance = vertget_the_distance(win,win->ray[i].ray_angle,  i);
        win->ray[i].ray_distance = compare_distance(horizray_distance,verray_distance,win,i);
        ray_angle += ray_step;
        i++;
    }
}


int main(int ac, char **av) 
{
    int fd;
    t_mlx *window = malloc(sizeof(t_mlx));
    
    if (ac != 2 || check_file(av[1]) == 0) 
    {
        printf("Error\n");
        return (1);
    }
    if(!window)
        return (1);
    window->map = malloc(sizeof(t_map));
    window->map->player = malloc(sizeof(t_player));
    if(!window->map)
        return (1);
    init__map(window->map);
    fd = open(av[1], O_RDONLY);
    if (fd == -1) 
    {
        printf("Error opening file\n");
        return 1;
    }
    if (parsing_map(window->map, fd, av[1]))
    {
        printf("Error\n");
        ft_free_window(&window);
        return (1);
    }
    window->mlx = mlx_init(WIDTH, HEIGHT, "cub3D",false);
    window->img = mlx_new_image(window->mlx, WIDTH, HEIGHT);
    window->img1 = mlx_new_image(window->mlx, 22,22);
    init_params(window);
    mlx_image_to_window(window->mlx, window->img, 0, 0);
    mlx_image_to_window(window->mlx, window->img1, 0, 0);
    mlx_loop_hook(window->mlx, hook_stuff, window);
    render_3d(window);
    // draw2d(window);
    adraw(window);
    mlx_loop(window->mlx);
    ft_free_window(&window);
    close(fd);
    return 0;
} 