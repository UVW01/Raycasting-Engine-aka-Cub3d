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

void	update_player_position(t_cub *cub)
{
	t_fcoords	temp_pos;
	double		temp_rot;
	int			steps;

	if (cub->player.walk_horizon != 0)
		steps = cub->player.walk_horizon * 8;
	else
		steps = cub->player.walk_dir * 8;
	temp_rot = cub->player.rot + deg2rad(cub->player.turn_dir * 4); 
	temp_rot += deg2rad(abs(cub->player.walk_horizon) * 90);
	temp_rot = normalize_angle(temp_rot);
	temp_pos.x = cub->player.pos.x + (cos(temp_rot) * steps);
	temp_pos.y = cub->player.pos.y + (sin(temp_rot) * steps);
	if (!cub->player.walk_horizon)
		cub->player.rot = temp_rot;
	if (!check_wall_colision(cub->player, temp_pos, cub->input.map_arr))
		cub->player.pos = temp_pos;
}
