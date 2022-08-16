#include "../cub3d.h"

void	my_mlx_pixel_put(t_img_args *data, int x, int y, int color)
{
	char	*dst;
    
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void DDA_util(t_dda dda, int *steps, float *Xinc, float *Yinc)
{
    int dx;
    int dy;

    dx = (dda.x1 - dda.x0);
    dy = (dda.y1 - dda.y0);
    if (abs(dx) > abs(dy))
        *steps = abs(dx);
    else
        *steps = abs(dy);
    *Xinc = (dx / (float)*steps);
    *Yinc = (dy / (float)*steps);
}

void DDA(t_dda dda, t_img_args *img)
{
    int steps;
    float Xinc;
    float Yinc;
    int i;

    i = 0;
    DDA_util(dda, &steps, &Xinc, &Yinc);
    float X = dda.x0;
    float Y = dda.y0;
    while (i <= steps)
    {
        my_mlx_pixel_put(img, X, Y, dda.color);
        X += Xinc;
        Y += Yinc;
        i++;
    }
}

void    draw_box(int x, int y, int color, t_img_args *img)
{
    t_dda   dda;
    int     i;
    int     j;

    dda.x0 = x;
    dda.y0 = y;
    i = 1;
    while(i <= 20)
    {
        j = 1;
        while(j <= 20)
        {
            dda.x1 = x + j;
            dda.y1 = y + i;
            dda.color = color;
            DDA(dda, img);
            j++;
        }
        i++;
    }
}

void    draw_player(int x, int y, int color, t_cub *cub)
{
    t_dda  dda;
    int i;
    int j;

    x -= 3;
    y -= 3;
    dda.x0 = x;
    dda.y0 = y;
    i = 1;
    while(i <= 6)
    {
        j = 1;
        while(j <= 6)
        {
            dda.x1 = x + j;
            dda.y1 = y + i;
            dda.color = color;
            DDA(dda, &cub->map_img);
            j++;
        }
        i++;
    }
}
