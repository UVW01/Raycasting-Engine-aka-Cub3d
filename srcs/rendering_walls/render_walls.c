#include "../cub3d.h"

static void	draw_square(t_icoords p0, t_icoords p1, t_img *img, int color)
{
    int y;
    int x;
    
    y = p0.y;
	while (y <= p1.y) 
	{
        x = p0.x;
        while (x <= p1.x)
        {
		    img_pixel_put(img, (t_icoords){.x = x, .y = y}, color);
            x++;
        }
		y++;
	}
}


void    render_walls(t_cub *cub, t_ray ray, t_wall walls)
{
    t_icoords   p0;
    t_icoords   p1;

    p0.x = ray.id;
    p0.y = (int)(WIN_HEIGHT / 2) - (walls.walls_height / 2);
    p1.x = ray.id + 1;
    p1.y = (int)(p0.y + walls.walls_height);
    draw_square(p0, p1, &cub->display.img, 0xFFFFFF);

}
