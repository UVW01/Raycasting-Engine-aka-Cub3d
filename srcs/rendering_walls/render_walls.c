#include "../cub3d.h"

static int get_x_offset(t_ray ray, t_texture texture)
{
    int x_offset;

    x_offset = 0;
    if (ray.grid_direction == HORIZONTAL)
        x_offset = ((int)ray.wall_hit.x % texture.width);
    else if (ray.grid_direction == VERTICAL)
        x_offset = ((int)ray.wall_hit.y % texture.width);
    return (x_offset);
}

static int get_pixels_from_texture(t_cub cub, t_icoords pos, t_ray ray)
{
    int *texture;
    int     bpp;
    int     size_line;
    int     endian;

    pos.y = (pos.y % cub.input.textures[1].height);
    pos.x = get_x_offset(ray, cub.input.textures[1]);
    texture = (int *)mlx_get_data_addr(cub.input.textures[1].img_ptr, &bpp, &size_line, &endian);
    return (texture[(pos.y * cub.input.textures[1].width) + pos.x]);
}

static void	draw_walls(t_icoords p0, t_icoords p1, t_img *img, t_cub cub, t_ray ray, t_wall walls)
{
    int y;
    int x;
    int color = 0;
    double y_texture;
    
    y_texture = 0;
    y = p0.y;
	while (y <= p1.y)
	{
        x = p0.x;
        color = get_pixels_from_texture(cub, (t_icoords){.x = x, .y = (int)y_texture}, ray);
        while (x <= p1.x)
        {
		    img_pixel_put(img, (t_icoords){.x = x, .y = y}, color);
            x++;
        }
        y_texture += (cub.input.textures[1].height / walls.walls_height);
		y++;
	}
}

void    render_walls(t_cub *cub, t_ray ray)
{
    t_wall  walls;
    t_icoords   p0;
    t_icoords   p1;

    ray.distance = (ray.distance * cos(ray.ray_angle - cub->player.rot));
    walls.ds_proj_plane = (WIN_WIDTH / 2) / tan(FOV_ANGLE / 2);
    walls.walls_height = (CUB_SIZE / ray.distance) * walls.ds_proj_plane;
    if (walls.walls_height > WIN_HEIGHT)
        walls.walls_height = WIN_HEIGHT;
    p0.x = ray.id;
    p0.y = (int)(WIN_HEIGHT / 2) - (walls.walls_height / 2);
    p1.x = ray.id + 1;
    p1.y = (int)(p0.y + walls.walls_height);
    draw_walls(p0, p1, &cub->display.img, *cub, ray, walls);
}
