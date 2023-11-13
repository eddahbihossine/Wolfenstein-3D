/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <abel-hid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 03:26:59 by abel-hid          #+#    #+#             */
/*   Updated: 2023/11/13 06:18:54 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


# include <stdio.h>
# include <stdlib.h>

# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <string.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
typedef struct	s_player
{
    double	x;
    double	y;
    double	dir_x;
    double	dir_y;
    double	plane_x;
    double	plane_y;
    double	move_speed;
    double	rot_speed;
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
}				t_map;

typedef struct	s_data
{
    void	*mlx_ptr;
    void	*mlx_win;
    void	*img;
    char	*addr;
    int    width;
    int    height;
    t_map  map;
  
}				t_data;

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



#endif



// 111111
// 100101
// 101001 map[i-1][j]
// 1101N1 map[i][j - 1] | map[i][j + 1]
// 11 1111 map[i+1][j]
// 1111111