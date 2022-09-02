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

static int get_pixels_from_texture(t_texture texture, t_icoords offset)
{
    int *txtur_ptr;
    int     bpp;
    int     size_line;
    int     endian;

    offset.y = (offset.y % texture.height);
    txtur_ptr = (int *)mlx_get_data_addr(texture.img_ptr, &bpp, &size_line, &endian);
    return (txtur_ptr[(texture.width * offset.y) + offset.x]);
}

static  int get_cardinal_point(t_ray ray)
{
    if (ray.grid_direction == HORIZONTAL)
    {
        if (ray.is_facing_up)
            return (NO);
        else
            return (SO);
    }
    if (ray.grid_direction == VERTICAL)
    {
        if (ray.is_facing_right)
            return (EA);
        else
            return (WE);
    }
    return (0);
}

static void	draw_walls(t_cub *cub, t_ray ray, t_wall wall)
{
    int         y;
    int         color = 0;
    int         ds;
    t_icoords   txtur_offset;
    int         cardinal_point;
    
    cardinal_point = get_cardinal_point(ray);
    txtur_offset.x = get_x_offset(ray, cub->input.textures[cardinal_point]);
    y = wall.p0.y;
	while (y <= wall.p1.y)
	{
        ds = (y + (wall.wall_height / 2) - (WIN_HEIGHT / 2));
        txtur_offset.y = (ds * ((double)cub->input.textures[cardinal_point].height / wall.wall_height));
        color = get_pixels_from_texture(cub->input.textures[cardinal_point], txtur_offset);
        color = shade_color(color, get_darkness_percent(ray.distance, 100));
		img_pixel_put(&cub->display.img, (t_icoords){.x = wall.p0.x, .y = y}, color);
		y++;
	}
}

void    render_walls(t_cub *cub, t_ray ray)
{
    t_wall  wall;

    ray.distance = (ray.distance * cos(ray.ray_angle - cub->player.rot));
    wall.ds_proj_plane = (WIN_WIDTH / 2) / tan(FOV_ANGLE / 2);
    wall.wall_height = (CUB_SIZE / ray.distance) * wall.ds_proj_plane;
    wall.p0.x = ray.id;
    wall.p0.y = (int)(WIN_HEIGHT / 2) - (wall.wall_height / 2);
    if (wall.p0.y < 0)
        wall.p0.y = 0;
    wall.p1.x = ray.id + 1;
    wall.p1.y = (int)(wall.p0.y + wall.wall_height);
    if (wall.p1.y > WIN_HEIGHT)
        wall.p1.y = WIN_HEIGHT;
    draw_walls(cub, ray, wall);
}
