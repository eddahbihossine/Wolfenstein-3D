/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 03:26:59 by abel-hid          #+#    #+#             */
/*   Updated: 2023/12/11 21:51:16 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


# include <stdio.h>
# include <stdlib.h>

# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
#include "./MLX42/include/MLX42/MLX42.h"
# include <string.h>
#define ESC 256
#define W 87
#define S 83
#define A 65
#define D 68
#define LEFT 263
#define RIGHT 262
#define DOWN 264
#define UP 265
#define WIDTH 800
#define HEIGHT 800
#ifndef BUFFER_SIZE
#define TEXTURE_NO 0
#define TEXTURE_SO 1
#define TEXTURE_WE 2
#define TEXTURE_EA 3
# define BUFFER_SIZE 42
#endif

typedef struct s_ray
{
   double ray_angle;
   double ray_distance;
   double wall_hit_x;
   double wall_hit_xt;
   double wall_hit_yt;
   double wall_hit_y;
   int was_hit_vertical;
   int is_ray_facing_up;
   int is_ray_facing_down;
   int is_ray_facing_left;
   int is_ray_facing_right;
    int wall_hit_content;
   
} t_ray;

typedef struct	s_player
{
    double x;
    double y;
    double fov;
    double angle;
    double number_rays;
   
}				t_player;

typedef struct  s_color
{
    int r;
    int g;
    int b;
}               t_color;

typedef struct  s_map_2d
{
    int xmin;
    int ymin;
    int x;
    int y;
}               t_map_2d;
typedef struct	s_map
{
    char	**map;
    int	map_width;
    int	map_height;
    char     *no;
    char     *so;
    char     *we;
    char     *ea;
    t_color  floor;
    t_color  ceiling;
    t_player *player;
}				t_map;

typedef struct s_mlx
{
    mlx_t    *mlx;
    mlx_image_t *img;
    mlx_image_t *img1;
    t_map *map;
    t_ray ray[WIDTH];
    mlx_texture_t *texture;
    t_map_2d map_2d;

    
} t_mlx;

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_get_line(char **str, char **line, int new_line);
char	*get_rest(char **str, int new_line);
int		ft_check_new_line(char *str);
int	ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
void	ft_free(char **s);
int size_line(char *line);
char	*ft_strtrim(char const *s1, char const *set);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

// parsing
int	check_file(char *file);
int is_space(char c);
char  *skip_space(char *line);
int is_digit(char c);
int	init_floor(t_map *map, char *ptr);
int	parsing_coma(char *line);
int	valid_range(int r, int g, int b);
int	init_ceiling(t_map *map, char *line);
int	size_line(char *line);
int	get_height(t_map *map);
int	get_width(char *line);
void	init_map(t_map *map, int size);
int	count_lines(char *str);
int	parsing_floor_ceiling(char **line);
int	is_empty(char *line);
char	*my_strdup(char *line);
int	get_floor(char *line, int *k, t_map *map);
int	get_east_texture(char *line, int *k, t_map *map);
int	get_west_texture(char *line, int *k, t_map *map);
int	get_south_texture(char *line, int *k, t_map *map);
int	get_north_texture(char *line, int *k, t_map *map);
int	check_empty_line(char *line, t_map *map);
void	all_texture(t_map *map, char *line, int *k);
int	get_ceiling(char *line, int *k, t_map *map);
void	get_map(t_map *map, int *k, int *i, char *line);
int	init_all(t_map *map, int fd, char *str);
char	*next_line(int *cout, char *line, int fd);
void	ft_free_map(t_map **map);
void	free_empty_line(t_map *map, int *i);
int	get_longest_line(t_map *map);
int	check_valid_map(t_map *map);
int	valid_position(t_map *map);
int	check_player_position(t_map *map);
int	update_map(t_map *map);
void	init_widht_height(t_map *map);
int	check_wall(t_map *map);
int	valid_walls(t_map *map);
int	valid_wall_help(t_map *map, int i, int j);
int front_wall(char *line);
int back_wall(char *line);
int	wall_check(t_map *map);
int	get_player_position(t_map *map);
int	open_texture(t_map *map);
int	parsing_map(t_map *map, int fd, char *str);
void	init__map(t_map *map);
void	moveright(t_mlx *mlx, double speed);
void	moveleft(t_mlx *mlx, double speed);
void	movebackward(t_mlx *mlx, double speed);
void	moveforward(t_mlx *mlx, double speed);
void	hook_stuff(void *params);
double	radians_to_degrees(double radians);
double	degrees_to_radians(double degrees);
int	check_wall_collision(t_mlx *win, double xx, double yy);
void	re_draw(t_mlx *win);
#endif
