/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 03:26:59 by abel-hid          #+#    #+#             */
/*   Updated: 2023/11/22 19:22:53 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


# include <stdio.h>
# include <stdlib.h>

# include <unistd.h>
# include <fcntl.h>
# include <math.h>
#include "./MLX42/include/MLX42/MLX42.h"
# include <string.h>
#define WIDTH 800
#define HEIGHT 800
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
typedef struct	s_player
{
    int	x;
    int	y;
}				t_player;

typedef struct  s_color
{
    int r;
    int g;
    int b;
}               t_color;

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
    t_player player;
}				t_map;

typedef struct s_mlx
{
    mlx_t    *mlx;
    mlx_image_t *img;
    t_map *map;
    
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


#endif
