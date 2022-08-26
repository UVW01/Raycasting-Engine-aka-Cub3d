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

	map_index.x = (int)pos.x / CUB_SIZE;
	map_index.y = (int)pos.y / CUB_SIZE;
	map_size.y = 0;
	map_size.x = 0;
	while (map_arr[map_size.y])
		++map_size.y;
	while (map_arr[map_index.y][map_size.x])
		++map_size.x;
	if (!(map_index.x < map_size.x) || !(map_index.y < map_size.y) || \
		map_arr[map_index.y][map_index.x] == '1')
		return (1);
	return (0);
}

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

void	move_horizontally(t_cub *cub, int walk_dir)
{
	t_fcoords	new_pos;
	float		new_rot;
	int			steps;

	steps = walk_dir * 4;
	new_rot = cub->player.rot + deg2rad(90);
	new_pos.x = cub->player.pos.x + (cos(new_rot) * steps);
	new_pos.y = cub->player.pos.y + (sin(new_rot) * steps);
	if (!check_wall_colision(new_pos, cub->input.map_arr))
		cub->player.pos = new_pos;
}

/* -------------------------------------------------------------------------- */

void	update_player_position(t_cub *cub)
{
	t_fcoords	temp_pos;
	float		temp_rot;
	t_player	*player;
	t_img		*img;
	int			steps;

	player = &cub->player;
	img = &cub->display.img;
	steps = player->walk_dir * 8;
	temp_rot = player->rot + deg2rad(player->turn_dir * 5);
	temp_rot = normalize_angle(temp_rot);
	temp_pos.x = player->pos.x + (cos(player->rot) * steps);
	temp_pos.y = player->pos.y + (sin(player->rot) * steps);
	if (!check_wall_colision(temp_pos, cub->input.map_arr))
	{
		player->pos = temp_pos;
		player->rot = temp_rot;
	}
}
