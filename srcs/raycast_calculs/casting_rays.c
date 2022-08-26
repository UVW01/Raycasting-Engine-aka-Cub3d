#include "../cub3d.h"

static void    init_ray_infos(t_ray *ray, t_player player)
{
    if (player.rot > 0 && player.rot < M_PI)
        ray->is_facing_down = true;
    else
        ray->is_facing_up = true;
    if (player.rot < (0.5 * M_PI) || player.rot > (1.5 * M_PI))
        ray->is_facing_right = true;
    else
        ray->is_facing_left = true;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void    casting_rays(t_cub *cub)
{
    t_ray   ray;
    int     i;

    ft_bzero(&ray, sizeof(t_ray));
    ray.ray_angle = (cub->player.rot - (FOV_ANGLE / 2));
    ray.ray_angle = normalize_angle(ray.ray_angle);
    i = -1;
    while(++i < 10)
    {
        init_ray_infos(&ray, cub->player);
        cast(cub, ray);
        ray.ray_angle += (FOV_ANGLE / 10);
    }

}
