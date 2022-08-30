/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:12:18 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/14 21:21:46 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/* -------------------------------------------------------------------------- */

void	draw_background(t_cub *cub)
{
	int		color;
	int		y;
	int		x;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		color = cub->input.ceil_clr;
		if (y >= WIN_HEIGHT / 2)
			color = cub->input.floor_clr;
		x = -1;
		while (++x < WIN_WIDTH)
			img_pixel_put(&cub->display.img, (t_icoords){.x = x, .y = y}, \
				color);
	}
}

/* -------------------------------------------------------------------------- */

/*
static void	draw_player(t_player *player, t_img *img, int size)
{
	t_fcoords	point;
	t_fcoords	new_pxl;
	t_fcoords	tmp_pxl;

	point = player->pos;
	new_pxl.x = point.x - (size / 2);
	new_pxl.y = point.y - (size / 2);
	while (new_pxl.y <= point.y + (size / 2))
	{
		tmp_pxl = (t_fcoords){.x = new_pxl.x + size, .y = new_pxl.y};
		draw_line(img, new_pxl, tmp_pxl, 0xFF0000);
		new_pxl.y++;
	}
}
*/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/*
static void	draw_square(t_icoords point, t_img *img, int color, int size)
{
	int	y;
	int	x;

	y = (point.y * size) - 1;
	while (++y <= (point.y * size) + size)
	{
		x = (point.x * size) - 1;
		while (++x <= (point.x * size) + size)
			img_pixel_put(img, (t_icoords){.x = x, .y = y}, color);
	}
}
*/

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

/*
void	draw_game_map(t_cub *cub)
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
			draw_square(loop, &cub->display.img, color, CUB_SIZE);
		}
	}
	draw_player(&cub->player, &cub->display.img, 1);
}
*/
