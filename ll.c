#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub3D.h"


int check_file(char *file)
{
    int i = 0;

    while (file[i]) 
    {
        if (file[i] == '.') 
        {
            if (file[i + 1] == 'c' && file[i + 2] == 'u' && file[i + 3] == 'b')
                return (1);
        }
        i++;
    }
    return (0);
}

int is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f')
        return (1);
    return (0);
}

char  *skip_space(char *line)
{
    int i = 0;
    char *ptr;
    while (is_space(line[i]))
        i++;
    ptr = ft_substr(line, i, ft_strlen(line) - i);
    return (ptr);
}

int is_digit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}
int parsing_coma(char *line)
{
    int i = 0;
    int count = 0;
    while (line[i] != '\0')
    {
        if(line[i] == ',')
            count++;
        i++;
    }
    if(count != 2)
        return (1);
    return (0);
}


int valid_range(int r, int g, int b)
{
    if(r < 0 || r > 255)
        return (1);
    if(g < 0 || g > 255)
        return (1);
    if(b < 0 || b > 255)
        return (1);
    return (0);
}

int init_floor(t_map *map, char *ptr) 
{
    char *tmp;
    char **split;

    tmp = skip_space(ptr);
    if(parsing_coma(tmp))
        return (free(tmp), 1);
    
    split = ft_split(tmp, ',');
    if(parsing_floor_ceiling(split))
    {
        ft_free(split);
        free(tmp);
        return (1);
    }
    map->floor.r = ft_atoi(split[0]);
    map->floor.g = ft_atoi(split[1]);
    map->floor.b = ft_atoi(split[2]);
    ft_free(split);
    free(tmp);
    if(valid_range(map->floor.r, map->floor.g, map->floor.b))
        return (1);
    return 0;
}

int init_ceiling(t_map *map, char *line)
{
    char *tmp;
    char **split;
    char *ptr;

    ptr = ft_substr(line, 1, ft_strlen(line));
    tmp = skip_space(ptr);
    if(parsing_coma(tmp))
        return (free(tmp),free(ptr),1);
    split = ft_split(tmp, ',');
    if(parsing_floor_ceiling(split))
        return (ft_free(split), free(tmp),free(ptr),1);
    map->ceiling.r = ft_atoi(split[0]);
    map->ceiling.g = ft_atoi(split[1]);
    map->ceiling.b = ft_atoi(split[2]);
    ft_free(split);
    free(tmp);
    free(ptr);
    if(valid_range(map->ceiling.r, map->ceiling.g, map->ceiling.b))
        return (1);
    return 0;
}

int  count_lines(char *str)
{
    int count = 0;
    char *line;
    int fd = open(str, O_RDONLY);

    while((line = get_next_line(fd)))
    {
        count++;
        free(line);
    }
    close(fd);
    return (count);
}
void init_map(t_map *map, int size)
{
    int i = 0;
    map->map = malloc(sizeof(char *) * (size + 1));
    while (i < size)
    {
        map->map[i] = NULL;
        i++;
    }
}
int get_width(char *line) 
{
    int i = 0;
    int count = 0;
    while (line[i] != '\0') 
    {
        if (line[i] == '1')
            count++;
        i++;
    }
    return count;
}

int get_height(t_map *map) 
{
    int i = 0;
    int count = 0;
    while (map->map[i] != NULL) 
    {
        count++;
        i++;
    }
    while(ft_strncmp(map->map[i - 1], "\0", 1) == 0)
    {
        i--;
        count--;
    }
    return count;
}

int size_line(char *line)
{
    int i = 0;
    while (line[i] != '\0' && line[i] != '\n')
        i++;
    return (i);
}

char *my_strdup(char *line)
{
    int i = 0;
    char *str = malloc(sizeof(char) * (size_line(line) + 1));
    while (line[i] != '\0' && line[i] != '\n')
    {
        str[i] = line[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

int is_empty(char *line)
{
    int i = 0;
    size_t count = 0;
    while(line[i] != '\0')
    {
        if(is_space(line[i]))
            count++;
        i++;
    }
    if(count == (ft_strlen(line)))
        return (1);
    return (0);

}

int get_north_texture(char *line, int *k, t_map *map)
{
    char *ptr;
    ptr = ft_substr(line, 2, size_line(line) -2);
    map->no = skip_space(ptr);
    free(ptr);
    *k += 1;
    return (0);
}

int get_south_texture(char *line, int *k, t_map *map)
{
    char *ptr;
    ptr = ft_substr(line, 2, size_line(line) -2);
    map->so = skip_space(ptr);
    free(ptr);
    *k += 1;
    return (0);
}

int get_west_texture(char *line, int *k, t_map *map)
{
    char *ptr;
    ptr = ft_substr(line, 2, size_line(line) -2);
    map->we = skip_space(ptr);
    free(ptr);
    *k += 1;
    return (0);
}

int get_east_texture(char *line, int *k, t_map *map)
{
    char *ptr;
    ptr = ft_substr(line, 2, size_line(line) -2);
    map->ea = skip_space(ptr);
    free(ptr);
    *k += 1;
    return (0);
}

int get_floor(char *line, int *k, t_map *map)
{
    char *ptr;
    ptr = ft_substr(line, 1, size_line(line) -1);
    if(init_floor(map, ptr))
    {
        free(ptr);
        return (1);
    }
    free(ptr);
    *k += 1;
    return (0);
}

void get_map(t_map *map, int *k , int *i, char *line)
{
    if(*k == 6)
    {
        map->map[*i] = my_strdup(line);
        *i += 1;   
    }
}

int get_ceiling(char *line, int *k, t_map *map)
{
    char *ptr;
    ptr = ft_substr(line, 1, size_line(line) -1);
    if(init_ceiling(map, ptr))
    {
        free(ptr);
        return (1);
    }
    free(ptr);
    *k += 1;
    return (0);
}

void all_texture(t_map *map, char *line, int *k)
{
    line = skip_space(line);
    if(line[0]== 'N' && line[1] == 'O' && !map->no)
        get_north_texture(line, k, map);
    else if(line[0]== 'S' && line[1] == 'O' && !map->so)
        get_south_texture(line, k, map);
    else if(line[0]== 'W' && line[1] == 'E' && !map->we)
        get_west_texture(line, k, map);
    else if(line[0]== 'E' && line[1] == 'A' && !map->ea)
        get_east_texture(line, k, map);
    else if(line[0]== 'C' && map->ceiling.r == -42)
        get_ceiling(line, k, map);
    else if(line[0]== 'F' && map->floor.r == -42)
        get_floor(line, k, map);
    free(line);
}

int check_empty_line(char *line, t_map *map)
{
   if(is_empty(line) == 1 && map->map[0] == NULL)
    {
        free(line);
        return (1);
    }
    return (0);
}

int init_all(t_map *map , int fd, char *str)
{
    char *line;
    int i;
    int count;
    int k;

    count = 0;
    i = 0;
    k = 0;
    init_map(map, count_lines(str));
    while((line = get_next_line(fd)))
    {
        if(check_empty_line(line, map))
            continue;
        if(count < 6)
            all_texture(map, line, &k);
        else
            get_map(map, &k, &i, line);
        free(line);
        count++;
    }
    map->map[i] = NULL;
    close(fd);
    if(k != 6)
        return (1);
    return (0);
}

void   ft_free_map(t_map **map)
{
    int i = 0;
    if((*map)->no)
    free((*map)->no);
    if((*map)->so)
    free((*map)->so);
    if((*map)->we)
    free((*map)->we);
    if((*map)->ea)
    free((*map)->ea);

    while ((*map)->map[i] != NULL)
    {
        free((*map)->map[i]);
        i++;
    }
    if((*map)->map)
    free((*map)->map);
    free(*map);
}

void f()
{
    system("leaks cub3D");
}

int check_player_position(t_map *map)
{
    int i = 0;
    int j = 0;
    int count = 0;
    t_map *tmp;
    tmp = map;
    while (tmp->map[i] != NULL)
    {
        j = 0;
        while (tmp->map[i][j] != '\0')
        {
            if (tmp->map[i][j] == 'N' || tmp->map[i][j] == 'S' || tmp->map[i][j] == 'W' || tmp->map[i][j] == 'E')
                count++;
            j++;
        }
        i++;
    }
    if (count != 1)
        return (1);
    return (0);
}


int check_valid_map(t_map *map)
{
    int i = 0;
    int j = 0;
    while (map->map[i] != NULL)
    {
        j = 0;
        if(strcmp(map->map[i], "\0") == 0)
            return (1);
        while (map->map[i][j] != '\0')
        {
            if (map->map[i][j] != '1' && map->map[i][j] != '0' && map->map[i][j] != 'N' && map->map[i][j] != 'S' && map->map[i][j] != 'W' && map->map[i][j] != 'E' && map->map[i][j] != ' ')
                return (1);
            j++;
        }
        i++;
    }
    i = 0;
    return (0);
}

int get_longest_line(t_map *map)
{
    int i = 0;
    int j = 0;
    int max = 0;
    while (map->map[i] != NULL)
    {
        j = 0;
        while (map->map[i][j] != '\0')
        {
            j++;
        }
        if (j > max)
            max = j;
        i++;
    }
    return (max);
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

void free_empty_line(t_map *map , int *i)
{
    while(map->map[*i] != NULL)
    {
        free(map->map[*i]);
        map->map[*i] = NULL;
        *i += 1;
    }
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
            if (map->map[i][j])
            {
                if(map->map[i][j] != '1' && map->map[i][j] != '0' && map->map[i][j] != 'N' && map->map[i][j] != 'S' && map->map[i][j] != 'W' && map->map[i][j] != 'E' && map->map[i][j] != ' ')
                    tmp[j] = '2';
                else
                    tmp[j] = map->map[i][j];
            }
            else
                tmp[j] = '\0';
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

int valid_position(t_map *map)
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
                if (map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' ' || map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' ')
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
                map->player->x = j;
                map->player->y = i;
                if(map->map[i][j] == 'N')
                    map->player->angle = 3 * M_PI / 2;
                if(map->map[i][j] == 'S')
                    map->player->angle = M_PI / 2;
                if(map->map[i][j] == 'W')
                    map->player->angle = M_PI;
                if(map->map[i][j] == 'E')
                    map->player->angle = 0;
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
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

void ft_free_window(t_mlx **window)
{
    ft_free_map(&(*window)->map);
    free((*window));
}
double rayfacing_up(double angle)
{
    return (angle > 0 && angle < M_PI);
}
int	has_wall(t_mlx *win, double x, double y)
{
	int	i;
	int	j;

	if (x < 0 || x > win->map->map_width * 64 || y < 0
		|| y > win->map->map_height * 64)
		return (1);
	i = floor(y / 64);
	j = floor(x / 64);
	if (i >= win->map->map_height || j >= win->map->map_width )
		return (1);
	return (win->map->map[i][j] == '1');
}

double distance_between_points(double x1, double y1, double x2, double y2)
{
    return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

double horizontal_intersect(t_mlx *win, int i)
{
    double xintercept;
    double yintercept;

    yintercept = floor(win->map->player->y / 64) * 64;
    if (win->ray[i].is_ray_facing_down)
        yintercept += 64;
    xintercept = win->map->player->x + (yintercept - win->map->player->y) / tan(win->ray[i].ray_angle);
    double ystep = 64;
    if (win->ray[i].is_ray_facing_up)
        ystep *= -1;
    double xstep = 64 / tan(win->ray[i].ray_angle);
    if (win->ray[i].is_ray_facing_left && xstep > 0)
        xstep *= -1;
    if (win->ray[i].is_ray_facing_right && xstep < 0)
        xstep *= -1;
    double next_horz_touch_x = xintercept;
    double next_horz_touch_y = yintercept;
    if(win->ray[i].is_ray_facing_up)
        next_horz_touch_y--;
    while (1)
    {
        if (has_wall(win, next_horz_touch_x, next_horz_touch_y))
            return (distance_between_points(win->map->player->x, win->map->player->y, next_horz_touch_x, next_horz_touch_y));
        else
        {
            next_horz_touch_x += xstep;
            next_horz_touch_y += ystep;
        }
    }
    return (0); 
}

double vertical_intersect(t_mlx *win, int i)
{
    double xintercept;
    double yintercept;

    xintercept = floor(win->map->player->x / 64) * 64;
    if (win->ray[i].is_ray_facing_right)
        xintercept += 64;
    yintercept = win->map->player->y + (xintercept - win->map->player->x) * tan(win->ray[i].ray_angle);
    double xstep = 64;
    if (win->ray[i].is_ray_facing_left)
        xstep *= -1;
    double ystep = 64 * tan(win->ray[i].ray_angle);
    if (win->ray[i].is_ray_facing_up && ystep > 0)
        ystep *= -1;
    if (win->ray[i].is_ray_facing_down && ystep < 0)
        ystep *= -1;
    double next_vert_touch_x = xintercept;
    double next_vert_touch_y = yintercept;
    if(win->ray[i].is_ray_facing_left)
        next_vert_touch_x--;
    while (1)
    {
        if (has_wall(win, next_vert_touch_x, next_vert_touch_y))
            return (distance_between_points(win->map->player->x, win->map->player->y, next_vert_touch_x, next_vert_touch_y));
        else
        {
            next_vert_touch_x += xstep;
            next_vert_touch_y += ystep;
        }
    }
    return (0); 
}



double rayfacing_left(double angle)
{
    return (angle > M_PI / 2 && angle < 3 * M_PI / 2);
}

void normalize_angle(t_ray *angle)
{
   angle->ray_angle = remainder(angle->ray_angle, 2 * M_PI);
    if(angle->ray_angle < 0)
          angle->ray_angle = (2 * M_PI) + angle->ray_angle;

    if(angle->ray_angle > M_PI)
        angle->is_ray_facing_up = 1;
    if(angle->ray_angle > M_PI /2 && angle->ray_angle < 3 * M_PI / 2)
        angle->is_ray_facing_left = 1;

    angle->is_ray_facing_right = !angle->is_ray_facing_left;
    angle->is_ray_facing_down = !angle->is_ray_facing_up;
}



void raycast(t_mlx *win)
{
    int i =0;
    double ray_angle;
    ray_angle = win->map->player->angle - (win->map->player->fov / 2);
    double distance_to_wallh;
    double distance_to_wallv;

    while(i < 1471)
    {
        win->ray[i].ray_angle = ray_angle;
        printf("ray_angle = %f\n", win->ray[i].ray_angle);
        normalize_angle(&win->ray[i]);
        distance_to_wallh = horizontal_intersect(win,win->ray[i].ray_angle);
        distance_to_wallv = vertical_intersect(win,win->ray[i].ray_angle);
        win->ray[i].ray_distance = distance_to_wallh;
        if(distance_to_wallh < distance_to_wallv)
        {
            win->ray[i].ray_distance = distance_to_wallh;
        }
        else
        {
            win->ray[i].ray_distance = distance_to_wallv;
        }
        ray_angle += win->map->player->fov / 1472;
        i++;
    }   
}



void render(t_mlx *win)
{

	double	correct_distance;
	double	projection_distance;
	int		i;


	projection_distance = (WIDTH / 2)
		/ tan((60 * (M_PI / 180)) / 2);
	i = -1;
	while (++i < WIDTH)
	{
		correct_distance = win->ray[i].ray_distance * cos(win->map->player->angle - win->ray[i].ray_angle);
		 double wall_strip_heightt = (projection_distance * 64) / correct_distance;
	int	y;
	int	y1;

	y1 = (HEIGHT / 2) - (wall_strip_heightt / 2);
	y = -1;
	while (++y < HEIGHT)
	{
		if (y < y1)
			mlx_put_pixel(win->img, i, y, 0x00000000);
		else if (y < y1 + wall_strip_heightt)
			mlx_put_pixel(win->img, i, y, 0xFFFFFFFF);
		else
			mlx_put_pixel(win->img, i, y, 0x00000000);
	}
	}
}

int check_wall_collision(t_mlx *win, double x, double y)
{
    int i;
    int j;
    i = floor(y / 64);
    j = floor(x / 64);
    if(i < 0 || i >= win->map->map_height || j < 0 || j >= win->map->map_width)
        return (1);
    return (win->map->map[i][j] == '1');    
}
int    player_movement(t_mlx *win)
{
    int	move_step;
	int	x;
	int	y;

	win->map->player->angle += win->turn_direction * 3.0 * (M_PI / 180);
	move_step = 2.0 * win->side_direction;
	if (check_wall_collision(win, win->map->player->x + cos(win->map->player->angle) * \
		move_step, win->map->player->y + sin(win->map->player->angle) * move_step))
		return (0);
	win->map->player->x += cos(win->map->player->angle) * move_step;
	win->map->player->y += sin(win->map->player->angle) * move_step;
	return (1);
}
void start_shit(t_mlx *win)
{
    if(!player_movement(win))
        return ;
    raycast(win);
    render(win);
}
void	key_w(t_mlx *player, mlx_key_data_t keydata)
{
	if (keydata.action == MLX_PRESS)
		player->side_direction = 1;
	else if (keydata.action == MLX_RELEASE)
		player->side_direction = 0;
}

void	key_right(t_mlx *player, mlx_key_data_t keydata)
{
	if (keydata.action == MLX_PRESS)
		player->turn_direction = 1;
	else if (keydata.action == MLX_RELEASE)
		player->turn_direction = 0;
}

void	key_left(t_mlx *player, mlx_key_data_t keydata)
{
	if (keydata.action == MLX_PRESS)
		player->turn_direction = -1;
	else if (keydata.action == MLX_RELEASE)
		player->turn_direction = 0;
}



void	key_func(mlx_key_data_t keydata, void *param)
{
	t_mlx	*player;

	player = param;
	if (keydata.key == MLX_KEY_W)
		key_w(player, keydata);
	// if (keydata.key == MLX_KEY_S)
	// 	key_s(player, keydata);
	if (keydata.key == MLX_KEY_LEFT)
		key_left(player, keydata);
	if (keydata.key == MLX_KEY_RIGHT)
		key_right(player, keydata);
	// if (keydata.key == MLX_KEY_A)
	// 	key_a(player, keydata);
	// if (keydata.key == MLX_KEY_D)
	// 	key_d(player, keydata);
	if (keydata.key == MLX_KEY_ESCAPE)
		exit (0);
}
// void print_stuff()
void hook_stuff(void *params)
{
   t_mlx *window = (t_mlx *)params;
   if(window->img)
        mlx_delete_image(window->mlx, window->img);
    window->img = mlx_new_image(window->mlx,WIDTH,HEIGHT);
    start_shit(window);
    mlx_image_to_window(window->mlx,window->img,0,0);


}
void init_params(t_mlx *window)
{
    window->turn_direction = 0;
    window->side_direction = 0;
    window->map->player->fov = 60 * (M_PI / 180);
    window->map->player->x = window->map->player->x * TILE_SIZE + TILE_SIZE / 2;
    window->map->player->y = window->map->player->y * TILE_SIZE + TILE_SIZE / 2;
    window->map->player->turn_direction = 0;
    window->map->player->walk_direction = 0;
}

  
int main(int ac, char **av) 
{
    int fd;
    t_mlx window;
    
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
    window.map = malloc(sizeof(t_map));
    window.map->player = malloc(sizeof(t_player));
    window.ray = malloc(sizeof(t_ray) * WIDTH +1);
    init__map(window.map);
    if (parsing_map(window.map, fd, av[1]))
    {
        printf("Error\n");

        return (1);

    }
    init_params(&window);

   window.mlx = mlx_init(WIDTH, HEIGHT, "./includes/cub3D",false);
   window.img = mlx_new_image(window.mlx, WIDTH, HEIGHT);
   printf("%d\n", window.map->map_height);
    printf("%d\n", window.map->map_width);
    printf("%f\n", window.map->player->x);
    printf("%f\n", window.map->player->y);
    printf("%f\n", window.map->player->angle);
    mlx_key_hook(window.mlx, &key_func, &window);
    mlx_loop_hook(window.mlx, &hook_stuff, &window);
   mlx_image_to_window(window.mlx, window.img, 0, 0);
    mlx_loop(window.mlx);

    close(fd);
    return 0;
} 