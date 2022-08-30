/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <haitkadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:12:18 by haitkadi          #+#    #+#             */
/*   Updated: 2022/08/14 21:21:46 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

static void cast_until_hit_wall(t_fcoords intrcpt, t_fcoords step, \
    t_intrsctn *wall_hit, t_cub *cub)
{
    while ((intrcpt.x > 0 && intrcpt.x < WIN_WIDTH) && \
        (intrcpt.y > 0 && intrcpt.y < WIN_HEIGHT))
    {
        if (check_wall_colision(intrcpt, cub->input.map_arr))
        {
            wall_hit->x_point = intrcpt.x;
            wall_hit->y_point = intrcpt.y;
            wall_hit->is_intersected = true;
            break ;
        }
        else
        {
            intrcpt.x += step.x;
            intrcpt.y += step.y;
        }
    }
}

static void horizi_intrsctn(t_cub *cub, t_ray *ray, t_intrsctn *wall_hit)
{
    t_fcoords    intrcpt;
    t_fcoords    step;

    intrcpt.y = floor(cub->player.pos.y / CUB_SIZE) * CUB_SIZE;
    if (ray->is_facing_down)
        intrcpt.y += CUB_SIZE;
    intrcpt.x = cub->player.pos.x + (intrcpt.y - cub->player.pos.y) / \
        tan(ray->ray_angle);
    step.y = CUB_SIZE;
    if (ray->is_facing_up)
        step.y *= -1;
    step.x = CUB_SIZE / tan(ray->ray_angle);
    if (ray->is_facing_left && step.x > 0)
        step.x *= -1;
    if (ray->is_facing_right && step.x < 0)
        step.x *= -1;
    if (ray->is_facing_up)
        intrcpt.y -= 1;
    cast_until_hit_wall(intrcpt, step, wall_hit, cub);
    
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

static void vert_intrsctn(t_cub *cub, t_ray *ray, t_intrsctn *wall_hit)
{
    t_fcoords    intrcpt;
    t_fcoords    step;

    intrcpt.x = floor(cub->player.pos.x / CUB_SIZE) * CUB_SIZE;
    if (ray->is_facing_right)
        intrcpt.x += CUB_SIZE;
    intrcpt.y = cub->player.pos.y + (intrcpt.x - cub->player.pos.x) * \
        tan(ray->ray_angle);
    step.x = CUB_SIZE;
    if (ray->is_facing_left)
        step.x *= -1;
    step.y = CUB_SIZE * tan(ray->ray_angle);
    if (ray->is_facing_up && step.y > 0)
        step.y *= -1;
    if (ray->is_facing_down && step.y < 0)
        step.y *= -1;
    if (ray->is_facing_left)
        intrcpt.x -= 1;
    cast_until_hit_wall(intrcpt, step, wall_hit, cub);
    
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static void store_distance(t_ray *ray, double distnce, t_intrsctn intersectin)
{
    ray->distance = distnce;
    ray->wall_hit.x = (float)intersectin.x_point;
    ray->wall_hit.y = (float)intersectin.y_point;
}


static void    calcul_distance(t_player p, t_ray *ray, t_intrsctn horiz, \
    t_intrsctn vert)
{
    t_fcoords   distance;

    ft_bzero(&distance, sizeof(t_fcoords));
    distance.x = dstnce_btwn_points(p.pos.x, p.pos.y, horiz.x_point, \
        horiz.y_point);
    distance.y = dstnce_btwn_points(p.pos.x, p.pos.y, vert.x_point, \
        vert.y_point);
    if (horiz.is_intersected && vert.is_intersected)
    {
        if (distance.x < distance.y)
            store_distance(ray, distance.x, horiz);
        else
            store_distance(ray, distance.y, vert);
    }
    else if (horiz.is_intersected)
        store_distance(ray, distance.x, horiz);
    else if (vert.is_intersected)
        store_distance(ray, distance.y, vert);
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void    cast(t_cub *cub, t_ray *ray)
{
    t_intrsctn  h_intersect;
    t_intrsctn  v_intersect;
    
    ft_bzero(&h_intersect, sizeof(t_intrsctn));
    ft_bzero(&v_intersect, sizeof(t_intrsctn));
    horizi_intrsctn(cub, ray, &h_intersect);
    vert_intrsctn(cub, ray, &v_intersect);
    calcul_distance(cub->player, ray, h_intersect, v_intersect);
}
