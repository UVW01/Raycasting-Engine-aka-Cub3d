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
    t_wall  walls;

    ft_bzero(&ray, sizeof(t_ray));
    ft_bzero(&walls, sizeof(t_wall));
    ray.ray_angle = (cub->player.rot - (FOV_ANGLE / 2));
    ray.ray_angle = normalize_angle(ray.ray_angle);
    i = -1;
    while(++i < RAYS_LENGTH)
    {
        init_ray_infos(&ray);
        cast(cub, &ray);
        // draw_fov(cub->player.pos, ray.wall_hit, &cub->display.img);
        ray.id = i;
        ray.distance = (ray.distance * cos(ray.ray_angle - cub->player.rot));
        walls.walls_height = (CUB_SIZE / ray.distance) * walls.ds_proj_plane;
        walls.ds_proj_plane = (WIN_WIDTH / 2) / tan(FOV_ANGLE / 2);
        render_walls(cub, ray, walls);
        ray.ray_angle += (FOV_ANGLE / RAYS_LENGTH);
    }
}
