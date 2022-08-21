/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:12:18 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/14 21:21:46 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -------------------------------------------------------------------------- */

void	draw_player(t_coords point, t_img *img, int size)
{
	t_coords	p;

	p.x = (point.x - (size / 2));
	p.y = (point.y - (size / 2));
	while (p.y <= point.y + (size / 2))
	{
		draw_line(img, p, (t_coords){.x = p.x + size, .y = p.y}, 0xFF0000);
		p.y++;
	}
}

/* -------------------------------------------------------------------------- */

static void	draw_square(t_coords point, t_img *img, int color)
{
	t_coords	p;

	p.x = point.x * 64;
	p.y = point.y * 64;
	while (p.y <= (point.y * 64) + 64)
	{
		draw_line(img, p, (t_coords){.x = p.x + 64, .y = p.y}, color);
		p.y++;
	}
}

/* -------------------------------------------------------------------------- */

void	draw_minimap(t_cub *cub)
{
	t_coords	loop;
	int			color;

	loop.y = -1;
	while (cub->input.map_arr[++loop.y])
	{
		loop.x = -1;
		while (cub->input.map_arr[loop.y][++loop.x])
		{
			color = 0xF0F0F0;
			if (cub->input.map_arr[loop.y][loop.x] == ' ')
				continue ;
			else if (cub->input.map_arr[loop.y][loop.x] == '1')
				color = 0x3F3F3F;
			draw_square((t_coords){.x = loop.x, .y = loop.y},\
				 &cub->display.img, color);
		}
	}
}

void	update_player_position(t_player *player, t_img *img)
{
	t_coords	new_pos;
	int			steps;

	steps = player->walk_dir * 4;
	player->rot += deg2rad(player->turn_dir * 4);
	player->pos.x = player->pos.x + (cos(player->rot) * steps);
	player->pos.y = player->pos.y + (sin(player->rot) * steps);
	new_pos.x = player->pos.x + (cos(player->rot) * 40);
	new_pos.y = player->pos.y + (sin(player->rot) * 40);
	draw_line(img, player->pos, new_pos, 0x00FF00);
}
