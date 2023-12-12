#include "../includes/cub3D.h"

double  normalize_angle(double  *angle)
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