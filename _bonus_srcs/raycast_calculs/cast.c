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

static	void	cast_until_hit_wall(t_cast_params params, t_cub *cub, \
	t_ray ray, int grid_dir)
{
	t_fcoords	new_intrcpt;

	while (1)
	{
		new_intrcpt = params.intrcpt;
		if (grid_dir == HORIZONTAL && ray.is_facing_up)
			new_intrcpt.y -= 1;
		if (grid_dir == VERTICAL && ray.is_facing_left)
			new_intrcpt.x -= 1;
		if (wall_colision(new_intrcpt, cub->input.map_arr))
		{
			params.wall_hit->x_point = params.intrcpt.x;
			params.wall_hit->y_point = params.intrcpt.y;
			params.wall_hit->is_intersected = true;
			break ;
		}
		else
		{
			params.intrcpt.x += params.step.x;
			params.intrcpt.y += params.step.y;
		}
	}
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

static	void	horizi_intrsctn(t_cub *cub, t_ray *ray, t_intrsctn *wall_hit)
{
	t_fcoords		intrcpt;
	t_fcoords		step;
	t_cast_params	params;

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
	params.intrcpt = intrcpt;
	params.step = step;
	params.wall_hit = wall_hit;
	cast_until_hit_wall(params, cub, *ray, HORIZONTAL);
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

static	void	vert_intrsctn(t_cub *cub, t_ray *ray, t_intrsctn *wall_hit)
{
	t_fcoords		intrcpt;
	t_fcoords		step;
	t_cast_params	params;

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
	params.intrcpt = intrcpt;
	params.step = step;
	params.wall_hit = wall_hit;
	cast_until_hit_wall(params, cub, *ray, VERTICAL);
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void	cast(t_cub *cub, t_ray *ray)
{
	t_intrsctn	h_intersect;
	t_intrsctn	v_intersect;

	h_intersect.is_intersected = false;
	v_intersect.is_intersected = false;
	ft_bzero(&h_intersect, sizeof(t_intrsctn));
	ft_bzero(&v_intersect, sizeof(t_intrsctn));
	horizi_intrsctn(cub, ray, &h_intersect);
	vert_intrsctn(cub, ray, &v_intersect);
	calcul_distance(cub->player, ray, h_intersect, v_intersect);
}
