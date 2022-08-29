#include "../cub3d.h"

static void    init_ray_infos(t_ray *ray)
{
    ray->is_facing_down = false;
    ray->is_facing_up = false;
    ray->is_facing_right = false;
    ray->is_facing_left = false;
    if (ray->ray_angle > M_PI && ray->ray_angle < (2 * M_PI))
        ray->is_facing_up = true;
    else
        ray->is_facing_down = true;
    if (ray->ray_angle < (0.5 * M_PI) || ray->ray_angle > (1.5 * M_PI))
        ray->is_facing_right = true;
    else
        ray->is_facing_left = true;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// static void	draw_fov(t_fcoords start_pos, t_fcoords end_pos, t_img *img)
// {
// 	draw_line(img, start_pos, end_pos, 0x0000FF);
// }
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void    casting_rays(t_cub *cub)
{
    t_ray   ray;
    int     i;

    ft_bzero(&ray, sizeof(t_ray));
    ray.ray_angle = (cub->player.rot - (FOV_ANGLE / 2));
    i = -1;
    while(++i < RAYS_LENGTH)
    {
        ray.ray_angle = normalize_angle(ray.ray_angle);
        init_ray_infos(&ray);
        cast(cub, &ray);
        // draw_fov(cub->player.pos, ray.wall_hit, &cub->display.img);
        ray.id = i;
        render_walls(cub, ray);
        ray.ray_angle += (FOV_ANGLE / RAYS_LENGTH);
    }
}
