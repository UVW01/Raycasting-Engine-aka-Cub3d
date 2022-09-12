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

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

int	wall_colision(t_fcoords pos, char **map_arr)
{
	t_icoords	exact_axis;
	t_icoords	map_max_index;

	exact_axis.x = (pos.x / CUB_SIZE);
	exact_axis.y = (pos.y / CUB_SIZE);
	map_max_index.y = 0;
	map_max_index.x = 0;
	while (map_arr[map_max_index.y])
		map_max_index.y++;
	if (exact_axis.y < 0 || exact_axis.y >= map_max_index.y)
		return (1);
	map_max_index.x = ft_strlen(map_arr[exact_axis.y]);
	if (exact_axis.x < 0 || exact_axis.x > map_max_index.x)
		return (1);
	if (map_arr[exact_axis.y][exact_axis.x] == '1')
		return (1);
	return (0);
}

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
