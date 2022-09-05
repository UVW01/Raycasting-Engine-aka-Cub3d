/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <haitkadi@student.42.fr           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:46:48 by haitkadi          #+#    #+#             */
/*   Updated: 2022/09/05 12:46:51 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	void	store_distance(t_ray *ray, double distnce, \
	t_intrsctn intersectin, char grid_dir)
{
	ray->distance = distnce;
	ray->wall_hit.x = intersectin.x_point;
	ray->wall_hit.y = intersectin.y_point;
	ray->grid_direction = grid_dir;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void	calcul_distance(t_player p, t_ray *ray, t_intrsctn horiz, \
	t_intrsctn vert)
{
	t_fcoords	distance;

	ft_bzero(&distance, sizeof(t_fcoords));
	distance.x = dstnce_btwn_points(p.pos, horiz);
	distance.y = dstnce_btwn_points(p.pos, vert);
	if (horiz.is_intersected && vert.is_intersected)
	{
		if (distance.x < distance.y)
			store_distance(ray, distance.x, horiz, HORIZONTAL);
		else
			store_distance(ray, distance.y, vert, VERTICAL);
	}
	else if (horiz.is_intersected)
		store_distance(ray, distance.x, horiz, HORIZONTAL);
	else if (vert.is_intersected)
		store_distance(ray, distance.y, vert, VERTICAL);
}
