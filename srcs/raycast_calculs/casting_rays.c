#include "../cub3d.h"

static void    init_ray_infos(t_ray *ray, t_player player)
{
    if (player.rot > 0 && player.rot < M_PI)
        ray->isFacingDown = true;
    else
        ray->isFacingUp = true;
    if (player.rot < (0.5 * M_PI) || player.rot > (1.5 * M_PI))
        ray->isFacingRight = true;
    else
        ray->isFacingLeft = true;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void    casting_rays(t_cub *cub)
{
    t_ray   ray;
    int     i;

    ft_bzero(&ray, sizeof(t_ray));
    ray.rayAngle = (cub->player.rot - (FOV_ANGLE / 2));
    ray.rayAngle = normalize_angle(ray.rayAngle);
    i = -1;
    // while(++i < RAYS_LENGTH)
    while(++i < 1)
    {
        init_ray_infos(&ray, cub->player);
        cast(cub, ray);
        ray.rayAngle += (FOV_ANGLE / RAYS_LENGTH);
        printf("____________________________________________________________\n");
    }

}
