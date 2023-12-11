#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub3D.h"








void f()
{
    system("leaks cub3D");
}



int check_wall(t_map *map)
{
    int i = 0;
    int j = 0;
    while (map->map[i] != NULL)
    {
        j = 0;
        while (map->map[i][j] != '\0')
        {
            if (map->map[i][j] == '2')
                    return (1);
            j++;
        }
        i++;
    }
    return (0);
}

void init_widht_height(t_map *map)
{
    map->map_width = get_longest_line(map);
    map->map_height = get_height(map);
}


char get_char(t_map *map, int i, int j)
{
   if (map->map[i][j])
    {
        if(map->map[i][j] != '1' && map->map[i][j] != '0' && map->map[i][j] != 'N' && map->map[i][j] != 'S' && map->map[i][j] != 'W' && map->map[i][j] != 'E' && map->map[i][j] != ' ')
            return ('2');
        else
            return (map->map[i][j]);
    }
    else
        return ('\0');
    return ('\0');
}

int update_map(t_map *map)
{
    int i;
    int j ;
    char *tmp;

    i = 0;
    j = 0;
    tmp = NULL;
    init_widht_height(map);
    while(i < map->map_height)
    {
        j = 0;
        tmp = malloc(sizeof(char) * (map->map_width + 1));
        while (j < map->map_width)
        {
           if((size_t)j < ft_strlen(map->map[i]))
                tmp[j] = get_char(map, i, j);
            else
                tmp[j] = ' ';
            j++;
        }
        tmp[j] = '\0';
        free(map->map[i]);
        map->map[i] = tmp;
        i++;
    }
    free_empty_line(map, &i);
    return (0);
}

int valid_wall_help(t_map *map, int i, int j)
{
    if(i == map->map_height - 1)
    {
        if (map->map[i][j]  == '0')
        {
            if(map->map[i][j - 1] == '0')
                return (1);
        }
    }
    if (map->map[i][j]  == '0')
    {
        if(map->map[i][j + 1] == '0')
            return (1);
    }
    return (0);
}

int valid_walls(t_map *map)
{
    int i ;
    int j;

    i = 0;
    while (map->map[i] != NULL)
    {
        j = 0;
        while (map->map[i][j] != '\0')
        {
            if (i == 0 || i == map->map_height - 1)
                if(valid_wall_help(map, i, j))
                    return (1);
            if (map->map[i][j] == '0' && i != 0 && i != map->map_height - 1 && j != 0 && j != map->map_width - 1)
            {
                if ((map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' ' || map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' ') \
                    || (map->map[i - 1][j] == '\0' || map->map[i + 1][j] == '\0' || map->map[i][j - 1] == '\0' || map->map[i][j + 1] == '\0'))
                    return (1);
                 
            }
            j++;
        }
        i++;
    }
    return (0);
}


int front_wall(char *line)
{
    int i ;
    char *wall;

    i = 0;
    wall = ft_strtrim(line, " ");
    while (wall[i] != '\0') 
    {
        while(wall[i] == ' ')
            i++;
        if (wall[i] != '1') 
        {
            free(wall);
            return 1;
        }
        i++;
    }
    free(wall);
    return (0);
}

int back_wall(char *line)
{
    int i;
    char *wall;

    i = 0;
    wall = ft_strtrim(line, " ");
    while (wall[i] != '\0') 
    {
        while(wall[i] == ' ')
            i++;
        if (wall[i] != '1') 
        {
            free(wall);
            return 1;
        }
        i++;
    }
    free(wall);
    return (0);
}
void raycast(t_mlx *win);
int wall_check(t_map *map) 
{
    int i;
    char *wall;

    i = 0;
    if (map == NULL || map->map == NULL || map->map[0] == NULL) 
        return 1;
    if(front_wall(map->map[0]))
        return (1);
    i = 1;
    while (map->map[i] != NULL) 
    {
        if(map->map[i + 1] == NULL)
            break;
        wall = ft_strtrim(map->map[i], " ");
        if (wall[0] != '1' || wall[ft_strlen(wall) - 1] != '1') 
        {
            free(wall);
            return 1;
        }
        free(wall);
        i++;
    }
    if(back_wall(map->map[i]))
        return (1);
    return 0;
}

int get_player_position(t_map *map)
{
    int i = 0;
    int j = 0;
    while (map->map[i] != NULL)
    {
        j = 0;
        while (map->map[i][j] != '\0')
        {
            if (map->map[i][j] == 'N' || map->map[i][j] == 'S' || map->map[i][j] == 'W' || map->map[i][j] == 'E')
            {
                // x and y are the coordinates of the player
                map->player->x = j* 64 + 32 ;
                map->player->y = i  *64 +32;
  
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}

int open_texture(t_map *map)
{
    int no;
    int so;
    int we;
    int ea;

    no = open(map->no, O_RDONLY);
    if(no == -1)
        return (1);
    so = open(map->so, O_RDONLY);
    if(so == -1)
        return (1);
    we = open(map->we, O_RDONLY);
    if(we == -1)
        return (1);
    ea = open(map->ea, O_RDONLY);
    if(ea == -1)
        return (1);
    return (close(no), close(so), close(we), close(ea), 0);
}
int parsing_map(t_map *map , int fd, char *str)
{
    if(init_all(map, fd, str) || check_player_position(map))
        return (1);
    if(update_map(map) || check_wall(map))
        return (1);
    if (get_player_position(map))
        return (1);
     if (check_valid_map(map))
        return (1);
    if (valid_walls(map))
        return (1);
    if (wall_check(map))
        return (1);
    if (valid_position(map))
        return (1);
    if(open_texture(map))
        return (1);
    return (0);
}

void init__map(t_map *map)
{
    map->no = NULL;
    map->so = NULL;
    map->we = NULL;
    map->ea = NULL;
    map->map = NULL;
    map->map_width = 0;
    map->map_height = 0;
    map->floor.r = -42;
    map->floor.g = 0;
    map->floor.b = 0;
    map->ceiling.r = -42;
    map->ceiling.g = 0;
    map->ceiling.b = 0;
}
double radians_to_degrees(double radians) {
    return radians * (180.0 / M_PI);
}

void ft_free_window(t_mlx **window)
{
    ft_free_map(&(*window)->map);
    free((*window));
}
double degrees_to_radians(double degrees) {
    return degrees * (M_PI / 180);
}
// void print_stuff()


int check_wall_collision(t_mlx *win, double xx, double yy)
{
    int x;
    int y;

    x = floor(xx / 64);
    y = floor(yy / 64);
        if(win->ray[0].ray_distance< 12 && win->ray[799].ray_distance  < 12)
        {
            if(win->ray[0].ray_distance < win->ray[799 /2].ray_distance &&  win->ray[799].ray_distance < win->ray[799 /2].ray_distance )
                return(6);
        }
    
    if (x < 0 || y < 0 || x > win->map->map_width || y > win->map->map_height)
        return (1);
    return (win->map->map[y][x] == '1');
}
void MoveForward(t_mlx *mlx, double speed)
{
     if(check_wall_collision(mlx,mlx->map->player->x + cos(mlx->map->player->angle) * speed,mlx->map->player->y+ cos(mlx->map->player->angle) * speed) == 6 )
        return ;
    if(check_wall_collision(mlx, mlx->map->player->x, mlx->map->player->y)
    || check_wall_collision(mlx, mlx->map->player->x + cos(mlx->map->player->angle) * speed, mlx->map->player->y + sin(mlx->map->player->angle) * speed))
        return ;
    mlx->map->player->x += cos(mlx->map->player->angle) * speed;
    mlx->map->player->y += sin(mlx->map->player->angle) * speed;
}

void MoveBackward(t_mlx *mlx, double speed)
{
   
   if(check_wall_collision(mlx,mlx->map->player->x + cos(mlx->map->player->angle) * speed,mlx->map->player->y+ cos(mlx->map->player->angle) * speed) == 6 )
        return ;
    if(check_wall_collision(mlx, mlx->map->player->x, mlx->map->player->y)|| check_wall_collision(mlx, mlx->map->player->x - cos(mlx->map->player->angle) * speed, mlx->map->player->y - sin(mlx->map->player->angle) * speed))
        return ;
    mlx->map->player->x -= cos(mlx->map->player->angle) * speed;
    mlx->map->player->y -= sin(mlx->map->player->angle) * speed;
}

void MoveLeft(t_mlx *mlx, double speed)
{
     if(check_wall_collision(mlx,mlx->map->player->x + cos(mlx->map->player->angle) * speed,mlx->map->player->y+ cos(mlx->map->player->angle) * speed) == 6 )
        return ;
    if(check_wall_collision(mlx, mlx->map->player->x, mlx->map->player->y) || check_wall_collision(mlx, mlx->map->player->x + cos(mlx->map->player->angle - M_PI_2) * speed, mlx->map->player->y + sin(mlx->map->player->angle - M_PI_2) * speed))
        return ;
    mlx->map->player->x += cos(mlx->map->player->angle - M_PI_2) * speed;
    mlx->map->player->y += sin(mlx->map->player->angle - M_PI_2) * speed;
}

void MoveRight(t_mlx *mlx, double speed)
{
     if(check_wall_collision(mlx,mlx->map->player->x + cos(mlx->map->player->angle) * speed,mlx->map->player->y+ cos(mlx->map->player->angle) * speed) == 6 )
        return ;
    if(check_wall_collision(mlx, mlx->map->player->x, mlx->map->player->y) || check_wall_collision(mlx, mlx->map->player->x + cos(mlx->map->player->angle + M_PI_2) * speed, mlx->map->player->y + sin(mlx->map->player->angle + M_PI_2) * speed))
        return ;
    mlx->map->player->x += cos(mlx->map->player->angle + M_PI_2) * speed;
    mlx->map->player->y += sin(mlx->map->player->angle + M_PI_2) * speed;
}

void print_values(t_mlx *mlx)
{
    int i =0;
    while(i < 800)
    {
        printf("%f\n",mlx->ray[i].ray_distance);
        // getchar();

    }

}
void render_3d(t_mlx *win);
void adraw(t_mlx *win);
void hook_stuff(void *params)
{
    t_mlx *win = (t_mlx *)params;



        mlx_delete_image(win->mlx, win->img);
        mlx_delete_image(win->mlx, win->img1);

        if (mlx_is_key_down(win->mlx, ESC))
            exit(0);
        if (mlx_is_key_down(win->mlx, W))
            MoveForward(win, 5);
        else if (mlx_is_key_down(win->mlx, S))
            MoveBackward(win, 5);
        else if (mlx_is_key_down(win->mlx, A))
            MoveLeft(win, 5);
        else if (mlx_is_key_down(win->mlx, D))
            MoveRight(win, 5);
        else if (mlx_is_key_down(win->mlx, LEFT))
            win->map->player->angle -= 0.04;
        else if (mlx_is_key_down(win->mlx, RIGHT))
            win->map->player->angle += 0.04;
        else if(mlx_is_mouse_down(win->mlx,0))
            win->map->player->angle += 0.04;
        else if(mlx_is_mouse_down(win->mlx,1))
            win->map->player->angle -= 0.04;
        win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
        win->img1 = mlx_new_image(win->mlx, WIDTH, HEIGHT);
        raycast(win);
        // print_values(win);
        render_3d(win);
        adraw(win);
}


// void draw2d(t_mlx *win)
// {
//     rsmatlplayer(win);
    
    
// }


int mlx_draw(t_mlx *win, int x, int y, int color)
{
    int i;
    int j;

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

int	has_wall(t_mlx *win, double x, double y);
void adraw(t_mlx *win)
{
    int xmin;
    int ymin;

    int x ;
    int y ;

    y = (int)win->map->player->y - 100;
    ymin =  9;
    while(ymin < 200)
    {
        x = (int)win->map->player->x - 100;
        xmin = 9;
        while(xmin < 200)
        {
            if(x > 9 && y > 9)
            {
                if(has_wall(win, x, y))
                {
                    mlx_put_pixel(win->img, ymin, xmin, 0xFFF34675);
                }
                else
                    mlx_put_pixel(win->img, ymin, xmin, 0x0DEADBF);
            }
            else
                mlx_put_pixel(win->img, ymin, xmin, 0x000000000);
            x++;
            xmin++;
        }
        y++;
        ymin++;
    }

    ymin = 9;
    while(ymin < 14)
    {
        xmin = 9;
        while(xmin < 14)
        {
            mlx_put_pixel(win->img, xmin + 100 , ymin + 100, 0x000000000);
            xmin++;
        }
        ymin++;
    }
    mlx_image_to_window(win->mlx, win->img, 0, 0);
}


int check_whichside(t_mlx *win)
{
    int i = 0;
    int j = 0;
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
void set_the_vision_angle(t_mlx *win, int side)
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
void init_params(t_mlx *win)
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
int check_intersection(t_mlx *win, int x, int y)
{   
       int        i;
        int        j;

        if (x < 0 || x > win->map->map_width  || y < 0
                || y > win->map->map_height)
                return (1);
        i = floor(y);
        j = floor(x);
        if (i >= win->map->map_height || j >= win->map->map_width )
                return (1);
        return (win->map->map[i][j] == '1');

}
int check_upordown(double ray_angle)
{
    if (ray_angle > 0 && ray_angle < M_PI)
        return (1);
    return (0);
}
int check_leftorrigh( double ray_angle)
{
    if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2)
        return (1);
    return (0);
}


int	has_wall(t_mlx *win, double x, double y)
{
	int	i;
	int	j;

	if (x < 0 || y < 0 || x > win->map->map_width * 64 || y > win->map->map_height * 64)
        return (1); 
    i = floor(y / 64);
    j = floor(x / 64);
    if (i >= win->map->map_height || j >= win->map->map_width)
        return (1);
    return (win->map->map[i][j] == '1');
}


double horizget_the_distance(t_mlx *win, double ray_angle, int i)
{
	double	xintercept;
	double	yintercept;
	yintercept = floor(win->map->player->y / 64)
		* 64;
	if (ray_angle > 0 && ray_angle < M_PI)
		yintercept += 64;
	xintercept = win->map->player->x + ((yintercept - win->map->player->y)
			/ tan(ray_angle));
	double	xstep;
	double	ystep;

	ystep = 64;
	if (ray_angle > M_PI)
		ystep *= -1;
	xstep = 64 / tan(ray_angle);
	if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2 && xstep > 0)
		xstep *= -1;
	if ((ray_angle < M_PI / 2 || ray_angle > 3 * M_PI  / 2) && xstep < 0)
		xstep *= -1;
	if (ray_angle > M_PI)
		yintercept -= 0.1;

	while (!has_wall(win, xintercept, yintercept))
	{
		xintercept += xstep;
		yintercept += ystep;

	}
    win->ray[i].wall_hit_xt = xintercept;
    win->ray[i].wall_hit_yt = yintercept;
    return (sqrt(pow(win->map->player->x - xintercept, 2) + pow(win->map->player->y - yintercept, 2)));
}



double vertget_the_distance(t_mlx *win, double ray_angle , int i)
{
	double	xintercept;
	double	yintercept;

	xintercept = floor(win->map->player->x / 64)
		* 64;
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