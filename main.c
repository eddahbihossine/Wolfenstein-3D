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

int parsing_floor_ceiling(char **line)
{
    int i = 0;
    int j ;
    while (line[i] != NULL)
    {
        j = 0;
        while(line[i][j] != '\0')
        {
            if(!is_digit(line[i][j]))
                return (1);
            j++;
        }
        i++;
    }
    if(i != 3)
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
                map->player->x = j * 64 + 32;
                map->player->y = i * 64 + 32;
                printf("player.y = %f\n", map->player->y);
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
double radians_to_degrees(double radians) {
    return radians * (180.0 / M_PI);
}

void ft_free_window(t_mlx **window)
{
    ft_free_map(&(*window)->map);
    free((*window));
}
double degrees_to_radians(double degrees) {
    return degrees * (M_PI / 180.0);
}
// void print_stuff()
void mlx_draw(t_mlx *win);

void MoveForward(t_mlx *mlx, double speed)
{
    mlx->map->player->x += cos(mlx->map->player->angle) * speed;
    mlx->map->player->y += sin(mlx->map->player->angle) * speed;
}

void MoveBackward(t_mlx *mlx, double speed)
{
    mlx->map->player->x -= cos(mlx->map->player->angle) * speed;
    mlx->map->player->y -= sin(mlx->map->player->angle) * speed;
}

void MoveLeft(t_mlx *mlx, double speed)
{
    mlx->map->player->x += cos(mlx->map->player->angle - M_PI_2) * speed;
    mlx->map->player->y += sin(mlx->map->player->angle - M_PI_2) * speed;
}

void MoveRight(t_mlx *mlx, double speed)
{
    mlx->map->player->x += cos(mlx->map->player->angle + M_PI_2) * speed;
    mlx->map->player->y += sin(mlx->map->player->angle + M_PI_2) * speed;
}

void hook_stuff(void *params)
{
    t_mlx *win = (t_mlx *)params;

        // mlx_image_to_window(win->mlx, win->img,0, 0);
    if (mlx_is_key_down(win->mlx, ESC))
        exit(0);

    if (mlx_is_key_down(win->mlx, W))
    {
        mlx_delete_image(win->mlx, win->img);
        win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
        MoveForward(win, 5);
        raycast(win);
        mlx_image_to_window(win->mlx, win->img,0, 0);
    }
    if (mlx_is_key_down(win->mlx, S))
    {
        mlx_delete_image(win->mlx, win->img);
        win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
        MoveBackward(win, 5);
        raycast(win);
        mlx_image_to_window(win->mlx, win->img,0, 0);
    }
    if (mlx_is_key_down(win->mlx, A))
    {
        mlx_delete_image(win->mlx, win->img);
        win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
        MoveLeft(win, 5);
        raycast(win);
        mlx_image_to_window(win->mlx, win->img,0, 0);
    }
    if (mlx_is_key_down(win->mlx, D))
    {
        mlx_delete_image(win->mlx, win->img);
        win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
        MoveRight(win, 5);
        raycast(win);
        mlx_image_to_window(win->mlx, win->img,0, 0);
    }
    if(mlx_is_key_down(win->mlx, LEFT))
    {
        mlx_delete_image(win->mlx, win->img);
        win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
        win->map->player->angle -= 0.1;
        raycast(win);
        mlx_image_to_window(win->mlx, win->img,0, 0);
    }
    if(mlx_is_key_down(win->mlx, RIGHT))
    {
        mlx_delete_image(win->mlx, win->img);
        win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
        win->map->player->angle += 0.1;
        raycast(win);
        mlx_image_to_window(win->mlx, win->img,0, 0);
    }

    if(mlx_is_key_down(win->mlx, UP))
    {
        mlx_delete_image(win->mlx, win->img);
        win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
        win->map->player->angle -= 0.1;
        raycast(win);
        mlx_image_to_window(win->mlx, win->img,0, 0);
    }
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
        win->map->player->angle =  3 * M_PI / 2;
    if (side == 2)
        win->map->player->angle =  M_PI / 2;
    if (side == 3)
        win->map->player->angle =  M_PI;
    if (side == 4)
        win->map->player->angle =  0;
}  
void init_params(t_mlx *win)
{
    win->map->player->fov = degrees_to_radians(60);
    win->map->player->number_rays = WIDTH; 
    set_the_vision_angle(win, check_whichside(win));
    win->ray->ray_angle = win->map->player->angle - (win->map->player->fov / 2);
}
int	xray_direction(double ray_angle)
{
	return (fabs(cos(ray_angle)) / cos(ray_angle));
}

int	yray_direction(double ray_angle)
{
	return (fabs(sin(ray_angle)) / sin(ray_angle));
}
int check_upordown(double ray_angle)
{
    if(ray_angle > 0 && ray_angle < M_PI)
        return (1);
    return (0);
}


bool check_leftorrigh(double ray_angle)
{
    // Assuming M_PI is defined in your environment, otherwise, use 3.14159265358979323846
    return (ray_angle > 0 && ray_angle < M_PI);
}

bool check_downorup(double ray_angle)
{
    // Assuming M_PI is defined in your environment, otherwise, use 3.14159265358979323846
    return (ray_angle > M_PI_2 && ray_angle < 3 * M_PI_2);
}

int check_intersection(t_mlx *win, int x, int y, double ray_angle)
{
    x = x / 64;
    y = y / 64;
    if(check_upordown(ray_angle))
        y -= 1;
    if(check_leftorrigh(ray_angle))
        x -= 1;
      if (x < 0 || y < 0 || y >= win->map->map_height || x >= win->map->map_width)
        return 1;  // Out of bounds
    return (win->map->map[y][x] == '1');
}



#include <math.h>

// ...

void normalsize_angle(double *angle)
{
    *angle = fmod(*angle, 2.0 * M_PI);
    if (*angle < 0)
        *angle += 2.0 * M_PI;
}
double vertget_the_distance(t_mlx *win, double ray_angle)
{
    double x_intercept;
    double y_intercept;
    double x_step;
    double y_step;

    normalsize_angle(&ray_angle);

    x_intercept = floor(win->map->player->x / 64) * 64;
    y_intercept = win->map->player->y + (x_intercept - win->map->player->x) * tan(ray_angle);

    if (check_leftorrigh(ray_angle))
        x_intercept += 64;

    x_step = 64;
    if (check_leftorrigh(ray_angle))
        x_step *= -1;

    y_step = 64 * tan(ray_angle);
    if ((ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI) && y_step > 0)
        y_step *= -1;
    if ((ray_angle > 0.5 * M_PI && ray_angle < 1.5 * M_PI) && y_step < 0)
        y_step *= -1;
    double next_vert_x = x_intercept;
    double next_vert_y = y_intercept;
    while (check_intersection(win, next_vert_x, next_vert_y, ray_angle) == 0 && next_vert_x >= 0 && next_vert_y >= 0)
    {
        next_vert_x += x_step;
        next_vert_y += y_step;
    }
    return sqrt(pow(win->map->player->x -next_vert_x, 2) + pow(win->map->player->y - next_vert_y, 2));
}

double horizget_the_distance(t_mlx *win, double ray_angle)
{
    double x_intercept;
    double y_intercept;
    double x_step;
    double y_step;

    y_intercept = floor(win->map->player->y / 64) * 64;
    x_intercept = win->map->player->x + (y_intercept - win->map->player->y) / tan(ray_angle);
    if (check_downorup(ray_angle))
        y_intercept += 64;
    y_step = 64;
    if (check_downorup(ray_angle))
        y_step *= -1;
    x_step = 64 / tan(ray_angle);
    if ((ray_angle < M_PI && ray_angle > 2 * M_PI) && x_step > 0)
        x_step *= -1;
    if (ray_angle > M_PI && ray_angle < 2 * M_PI && x_step < 0)
        x_step *= -1;
    double next_horiz_x = x_intercept;
    double next_horiz_y = y_intercept;
    while (check_intersection(win, next_horiz_x, next_horiz_y, ray_angle) == 0 && next_horiz_x >= 0 && next_horiz_y >= 0)
    {
        next_horiz_x += x_step;
        next_horiz_y += y_step;
    }

    return sqrt(pow(win->map->player->x - next_horiz_x, 2) + pow(win->map->player->y - next_horiz_y, 2));
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

void render_3d(t_mlx *win)
{
    for(int i = 0; i <win->map->player->number_rays; i++)
    {
        t_ray ray = win->ray[i];
        double distance = ray.ray_distance;
        double distance_projection_plane = (WIDTH / 2) / tan(win->map->player->fov / 2);
        double wall_strip_height = (64 / distance) * distance_projection_plane;
        
        int wall_top_pixel = (HEIGHT / 2) - (wall_strip_height / 2);
        wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;
        int wall_bottom_pixel = (HEIGHT / 2) + (wall_strip_height / 2);
        wall_bottom_pixel = wall_bottom_pixel > HEIGHT ? HEIGHT : wall_bottom_pixel;
        int color = 0;
        if(ray.was_hit_vertical)
            color = 0x00BADA55;
        else
            color = 0x0DEDDEAD;

        for(int y = 0; y < wall_top_pixel; y++)
          mlx_put_pixel(win->img, i, y, 0xDAdad);
        for(int y = wall_top_pixel; y < wall_bottom_pixel; y++)
            mlx_put_pixel(win->img, i, y, color);
        for(int y = wall_bottom_pixel; y < HEIGHT; y++)
            mlx_put_pixel(win->img, i, y, 0x000000FF);
    }
}

void raycast(t_mlx *win)
{
    int i =0;
    double ray_angle =  win->map->player->angle - (degrees_to_radians(60)/2);
    double horizray_distance;
    double verray_distance;
    double ray_step;
    ray_step = win->map->player->fov / WIDTH;

    while(i < WIDTH)
    {
        normalsize_angle(&ray_angle);
        win->ray[i].ray_angle = ray_angle;
        horizray_distance = horizget_the_distance(win, ray_angle);
        verray_distance = vertget_the_distance(win,ray_angle);
        win->ray[i].ray_distance = compare_distance(horizray_distance,verray_distance,win,i);
        ray_angle += ray_step;
        i++;
    }
    render_3d(win);
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
    // printf("%s\n", window->map->no);
    // printf("%s\n", window->map->so);
    // printf("%s\n", window->map->we);
    // printf("%s\n", window->map->ea);
    // printf("%d\n", window->map->floor.r);
    // printf("%d\n", window->map->floor.g);
    // printf("%d\n", window->map->floor.b);
    // printf("%d\n", window->map->ceiling.r);
    // printf("%d\n", window->map->ceiling.g);
    // printf("%d\n", window->map->ceiling.b);
    // int i = 0;
    // while (window->map->map[i] != NULL)
    // {
    //     printf("%s\n", window->map->map[i]);
    //     i++;
    // }
    window->mlx = mlx_init(WIDTH, HEIGHT, "cub3D",false);
    window->img = mlx_new_image(window->mlx, WIDTH, HEIGHT);
    // printf("player.x = %f\n", window->map->player->x);
    // printf("player.y = %f\n", window->map->player->y);
    init_params(window);
    raycast(window);
    
    // mlx_draw(window);
    mlx_image_to_window(window->mlx, window->img, 0, 0);
    mlx_loop_hook(window->mlx, hook_stuff, window);
    mlx_loop(window->mlx);
    ft_free_window(&window);
    close(fd);
    return 0;
} 