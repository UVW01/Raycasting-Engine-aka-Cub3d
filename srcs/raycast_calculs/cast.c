#include "../cub3d.h"

static void horizIntersectionUtil(t_fcoords intrcpt, t_fcoords step, t_icoords *wallHit, t_cub *cub)
{
    while ((intrcpt.x > 0 && intrcpt.x < WIN_WIDTH) && (intrcpt.y > 0 && intrcpt.y < WIN_HEIGHT))
    {
        if (hasWallAtPos(cub->input.map_arr, intrcpt.x, intrcpt.y))
        {
            wallHit->x = floor(intrcpt.x);
            wallHit->y = floor(intrcpt.y);
            //printf("H-intersept |X%d| |Y%d|\n", wallHit->x, wallHit->y);
            break ;
        }
        else
        {
            intrcpt.x += step.x;
            intrcpt.y += step.y;
        }
    }
}

static void horizIntersection(t_cub *cub, t_ray *ray)
{
    t_fcoords    intrcpt;
    t_fcoords    step;
    t_icoords    wallHit;

    intrcpt.y = floor(cub->player.pos.y / CUB_SIZE) * CUB_SIZE;
    if (ray->isFacingDown)
        intrcpt.y += CUB_SIZE;
    intrcpt.x = cub->player.pos.x + (intrcpt.y - cub->player.pos.y) / tan(ray->rayAngle);
    step.y = CUB_SIZE;
    if (ray->isFacingUp)
        step.y *= -1;
    step.x = CUB_SIZE / tan(ray->rayAngle);
    if (ray->isFacingLeft && step.x > 0)
        step.x *= -1;
    if (ray->isFacingRight && step.x < 0)
        step.x *= -1;
    if (ray->isFacingUp)
        intrcpt.y--;
    horizIntersectionUtil(intrcpt, step, &wallHit, cub);
    // while ((intrcpt.x > 0 && intrcpt.x < WIN_WIDTH) && (intrcpt.y > 0 && intrcpt.y < WIN_HEIGHT))
    // {
    //     if (hasWallAtPos(cub->input.map_arr, intrcpt.x, intrcpt.y))
    //     {
    //         wallHit.x = floor(intrcpt.x);
    //         wallHit.y = floor(intrcpt.y);
    //         printf("H-intersept |X%d| |Y%d|\n", wallHit.x, wallHit.y);
    //         break ;
    //     }
    //     else
    //     {
    //         intrcpt.x += step.x;
    //         intrcpt.y += step.y;
    //     }
    // }
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// static t_intersection vertIntersection(t_cub *cub, t_ray *ray)
// {

// }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

// static void    calcul_distance(t_ray *ray)
// {

// }

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void    cast(t_cub *cub, t_ray ray)
{
    t_intersection  H_Intersect;
    t_intersection  V_Intersect;
    // ray.rayAngle = normalize_angle(ray.rayAngle);
    ft_bzero(&H_Intersect, sizeof(t_intersection));
    ft_bzero(&V_Intersect, sizeof(t_intersection));
    horizIntersection(cub, &ray);
    // V_Intersect = vertIntersection(cub, &ray);
    // calcul_distance(&ray);
}
