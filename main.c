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

int min_line(t_map *map)
{
    int i;
    int min;
    int k ;
    int j;

    i = 0;
    k = 0;
    min = map->map_width;
    while(ft_strncmp(map->map[i], "\0", 1) == 0)
    {
        i++;
        k++;
    }
    while (map->map[i] != NULL)
    {
        j = 0;
        while (map->map[i][j] != '\0')
            j++;
        if (j < min)
            min = j;
        i++;
    }
    if(min < 6 || i - k < 5)
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
    if(min_line(map))
        return (1);
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
                if (map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' ' || map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' ')
                    return (1);
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
                map->player.x = j;
                map->player.y = i;
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
    if((*window)->map)
        ft_free_map(&(*window)->map);
    if((*window)->mlx)
        free((*window)->mlx);
    if((*window)->img)
        free((*window)->img);
    free(*window);
}

int main(int ac, char **av) 
{
    int fd;
    t_mlx *window;
    window = malloc(sizeof(t_mlx));
    atexit(f);

    if (ac != 2 || check_file(av[1]) == 0) 
    {
        printf("Error\n");
        return (1);
    }
    window->map = malloc(sizeof(t_map));

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
   
    // printf("%s\n", map->no);
    // printf("%s\n", map->so);
    // printf("%s\n", map->we);
    // printf("%s\n", map->ea);
    // printf("%d\n", map->floor.r);
    // printf("%d\n", map->floor.g);
    // printf("%d\n", map->floor.b);
    // printf("%d\n", map->ceiling.r);
    // printf("%d\n", map->ceiling.g);
    // printf("%d\n", map->ceiling.b);

    int i = 0;
    while(window->map->map[i] != NULL)
    {
        printf("%s\n", window->map->map[i]);
        i++;
    }
    ft_free_window(&window);
    close(fd);
    return 0;
} 
