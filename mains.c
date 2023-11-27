#include "MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    mlx_t *mlx = malloc(sizeof(mlx_t));
    mlx_image_t *img = malloc(sizeof(mlx_image_t));
    mlx = mlx_init(300,300,"test",false);
    img = mlx_new_image(mlx, 300, 300);
    for (int i = 0; i < 300; i++)
    {
        for (int j = 0; j < 300; j++)
        {
            mlx_put_pixel(img, i, j, 0x00);
        }
    }
    mlx_image_to_window(mlx, img, 0, 0);

    mlx_loop(mlx);

}