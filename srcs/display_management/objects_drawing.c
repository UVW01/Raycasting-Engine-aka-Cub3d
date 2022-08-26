/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_drawing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:12:18 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/14 21:21:46 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -------------------------------------------------------------------------- */

void	draw_background(t_img *img, t_input *input)
{
	int	y0;
	int	y1;

	y0 = 0;
	y1 = WIN_HEIGHT / 2;
	while (y0 <= y1)
	{
		draw_line(img, (t_fcoords){.x = 0, .y = y0}, \
			(t_fcoords){.x = WIN_WIDTH, .y = y0}, input->ceil_clr);
		++y0;
	}
	y0 = WIN_HEIGHT / 2;
	y1 = WIN_HEIGHT;
	while (y0 <= y1)
	{
		draw_line(img, (t_fcoords){.x = 0, .y = y0}, \
			(t_fcoords){.x = WIN_WIDTH, .y = y0}, input->floor_clr);
		++y0;
	}
}

/* -------------------------------------------------------------------------- */

static void	draw_center_of_fov(t_fcoords pos, double rot, t_img *img)
{
	t_fcoords	new_pos;

	new_pos.x = pos.x + (cos(rot) * 160);
	new_pos.y = pos.y + (sin(rot) * 160);
	draw_line(img, pos, new_pos, 0x0000FF);
}

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

void	draw_player(t_player *player, t_img *img, int size)
{
	t_fcoords	point;
	t_fcoords	new_pxl;
	t_fcoords	tmp_pxl;

	point = player->pos;
	new_pxl.x = point.x - (size / 2);
	new_pxl.y = point.y - (size / 2);
	draw_center_of_fov(player->pos, player->rot, img);
	while (new_pxl.y <= point.y + (size / 2))
	{
		tmp_pxl = (t_fcoords){.x = new_pxl.x + size, .y = new_pxl.y};
		draw_line(img, new_pxl, tmp_pxl, 0xFF0000);
		new_pxl.y++;
	}
}

/* -------------------------------------------------------------------------- */

static void	draw_square(t_icoords point, t_img *img, int color)
{
	t_icoords	p;

	p.x = (point.x * CUB_SIZE) + 1; // should remove the + 1
	p.y = (point.y * CUB_SIZE) + 1; // also here
	while (p.y <= (point.y * CUB_SIZE) + (CUB_SIZE - 1)) // should be 64
	{
		draw_line(img, (t_fcoords){.x = p.x, .y = p.y}, \
			(t_fcoords){.x = p.x + (CUB_SIZE - 1), .y = p.y}, color);
		p.y++;
	}
}

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

void	draw_minimap(t_cub *cub)
{
	t_icoords	loop;
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
			draw_square((t_icoords){.x = loop.x, .y = loop.y}, \
				&cub->display.img, color);
		}
	}
}
