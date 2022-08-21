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
	t_coords	p0;
	t_coords	p1;

	p0.x = point.x * 64;
	p0.y = point.y * 64;
	p1.x = p0.x;
	p1.y = p0.y + 64;
	while (++p.y <= (point.y * 64) + 63)
	{
		draw_line(img, p, (t_coords){.x =( p.x + 64) - 1, .y = p.y}, color);
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

void	draw_fov(t_cub *cub)
{
	t_coords	new_pos;

	new_pos.x = cub->player.pos.x * cos(cub->player.rot);
	new_pos.y = cub->player.pos.y * sin(cub->player.rot);
	draw_line(&cub->display.img, cub->player.pos, new_pos, 0x00FF00);
}
