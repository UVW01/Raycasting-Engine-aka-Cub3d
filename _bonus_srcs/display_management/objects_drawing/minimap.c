/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:12:18 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/14 21:21:46 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/* -------------------------------------------------------------------------- */

static void	draw_minimap_base(t_cub *cub, int scale, int offset)
{
	t_icoords	pixel;
	int			size;

	size = WIN_HEIGHT / scale;
	pixel.y = -1;
	while (++pixel.y < size)
	{
		pixel.x = -1;
		while (++pixel.x < size)
			img_pixel_put(&cub->display.img, pixel, 0);
	}
	pixel.y = offset;
	while (pixel.y < size - offset)
	{
		pixel.x = offset - 1;
		while (++pixel.x < size - offset)
			img_pixel_put(&cub->display.img, pixel, 0x202020);
		pixel.y++;
	}
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

static void	draw_object(t_icoords obj, t_cub *cub, int color)
{
	t_icoords	loop;
	t_icoords	p_offset;
	t_icoords	pixel;
	t_fcoords	player_pos;
	int			size;

	size = (WIN_HEIGHT / 4) / 11;
	player_pos = cub->player.pos;
	p_offset.x = ((player_pos.x * size) / CUB_SIZE);
	p_offset.y = ((player_pos.y * size) / CUB_SIZE);
	loop.y = (obj.y * size) - 1;
	while (++loop.y <= (obj.y * size) + size)
	{
		loop.x = (obj.x * size) - 1;
		while (++loop.x <= (obj.x * size) + size)
		{
			pixel.x = (loop.x - p_offset.x) + ((WIN_HEIGHT / 4) / 2);
			pixel.y = (loop.y - p_offset.y) + ((WIN_HEIGHT / 4) / 2);
			if (pixel.x > cub->display.img.m_offset \
				&& pixel.y > cub->display.img.m_offset \
				&& pixel.x <= (WIN_HEIGHT / 4) - cub->display.img.m_offset \
				&& pixel.y <= (WIN_HEIGHT / 4) - cub->display.img.m_offset)
				img_pixel_put(&cub->display.img, pixel, color);
		}
	}
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

static void	draw_minimap_objects(t_cub *cub, int scale, int offset)
{
	t_icoords	loop;
	int			color;
	int			size;

	size = WIN_HEIGHT / scale;
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
			cub->display.img.m_offset = offset;
			draw_object(loop, cub, color);
		}
	}
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void	draw_minimap(t_cub *cub)
{
	int	scale;
	int	offset;

	scale = 4;
	offset = (WIN_HEIGHT / scale) / 30;
	draw_minimap_base(cub, scale, offset);
	draw_minimap_objects(cub, scale, offset);
	draw_minimap_player(cub, scale);
}
