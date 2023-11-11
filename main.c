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
    while (is_space(line[i]))
        i++;
    return (&line[i]);
}

int init_floor(t_map *map, char *line) 
{
    char *tmp;
    char **split;

    tmp = skip_space(ft_substr(line, 1, ft_strlen(line)));
    split = ft_split(tmp, ',');
    map->floor.r = ft_atoi(split[0]);
    map->floor.g = ft_atoi(split[1]);
    map->floor.b = ft_atoi(split[2]);
    ft_free(split);
    return 0;
}

int init_ceiling(t_map *map, char *line)
{
    char *tmp;
    char **split;

    tmp = skip_space(ft_substr(line, 1, ft_strlen(line)));
    split = ft_split(tmp, ',');
    map->ceiling.r = ft_atoi(split[0]);
    map->ceiling.g = ft_atoi(split[1]);
    map->ceiling.b = ft_atoi(split[2]);
    ft_free(split);
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
    }
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
int init_all(t_map *map , int fd, char *str)
{
    char *line;
    int i = 0;
    int count = 0;
    int j = count_lines(str);
    init_map(map, j);

    while((line = get_next_line(fd)))
    {
        if(count <= 6)
        {
            if(line[0]== 'N' && line[1] == 'O')
                map->no = skip_space(ft_substr(line, 2, ft_strlen(line)));
            else if(line[0]== 'S' && line[1] == 'O')
                map->so = skip_space(ft_substr(line, 2, ft_strlen(line)));
            else if(line[0]== 'W' && line[1] == 'E')
                map->we = skip_space(ft_substr(line, 2, ft_strlen(line)));
            else if(line[0]== 'E' && line[1] == 'A')
                map->ea = skip_space(ft_substr(line, 2, ft_strlen(line)));
            else if(line[0]== 'C')
                init_ceiling(map, line);
            else if(line[0]== 'F')
                init_floor(map, line);
        }
        else
        {
            map->map[i] = ft_strdup(line);
            i++;
        }
        count++;
    }
    return (0);
}



int main(int ac, char **av) 
{
    int fd;
    t_map map;

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

    if(init_all(&map, fd, av[1]))
        return (0);
   
    printf("%s", map.no);
    printf("%s", map.so);
    printf("%s", map.we);
    printf("%s", map.ea);
    printf("%d\n", map.floor.r);
    printf("%d\n", map.floor.g);
    printf("%d\n", map.floor.b);
    printf("%d\n", map.ceiling.r);
    printf("%d\n", map.ceiling.g);
    printf("%d\n", map.ceiling.b);

    int i = 0;
    while (map.map[i] != NULL)
    {
        printf("%s", map.map[i]);
        i++;
    }

    

    

    return 0;
}
