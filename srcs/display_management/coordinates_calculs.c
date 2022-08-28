/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates_calculs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:12:18 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/14 21:21:46 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -------------------------------------------------------------------------- */

static int	check_wall_colision(t_fcoords pos, char **map_arr)
{
	t_icoords	map_index;
	t_icoords	map_size;

	map_index = (t_icoords){.x = pos.x / CUB_SIZE, .y = pos.y / CUB_SIZE};
	map_size = (t_icoords){.x = 0, .y = 0};
	while (map_arr[map_size.y])
		++map_size.y;
	if (map_index.y >= map_size.y || map_index.y < 0)
		return (1);
	map_size.x = ft_strlen(map_arr[map_index.y]);
	if (map_index.x >= map_size.x || map_index.x < 0 || \
		 map_arr[map_index.y][map_index.x] == '1')
		return (1);
	return (0);
}

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

void	update_player_position(t_cub *cub)
{
	t_fcoords	temp_pos;
	double		temp_rot;
	int			steps;

	if (cub->player.walk_horizon != 0)
		steps = cub->player.walk_horizon * 4;
	else
		steps = cub->player.walk_dir * 4;
	temp_rot = cub->player.rot + deg2rad(cub->player.turn_dir * 4); 
	temp_rot += deg2rad(abs(cub->player.walk_horizon) * 90);
	temp_rot = normalize_angle(temp_rot);
	temp_pos.x = cub->player.pos.x + (cos(temp_rot) * steps);
	temp_pos.y = cub->player.pos.y + (sin(temp_rot) * steps);
	if (cub->player.walk_horizon == 0)
		cub->player.rot = temp_rot;
	if (!check_wall_colision(temp_pos, cub->input.map_arr))
		cub->player.pos = temp_pos;
}
