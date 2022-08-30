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

void	draw_player(t_player *player, t_img *img, int size)
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

/* -------------------------------------------------------------------------- */

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

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

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
}

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
			img_pixel_put(&cub->display.img, pixel, 0x303030);
	}
	pixel.y = offset;
	while (pixel.y < size - offset)
	{
		pixel.x = offset - 1;
		while (++pixel.x < size - offset)
			img_pixel_put(&cub->display.img, pixel, 0);
		pixel.y++;
	}
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

static void	draw_minimap_player(t_cub *cub, int scale)
{
	t_icoords	new_pos;
	int			size;

	size = WIN_HEIGHT / scale;
	new_pos = (t_icoords){.x = (size / 2), .y = (size / 2)};
	img_pixel_put(&cub->display.img, new_pos, 0xFF0000);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

static void	draw_object_square(t_icoords p, t_img *img, int color, int size, \
	int offset)
{
	int	y;
	int	x;

	y = (p.y * size) - 1;
	while (++y <= (p.y * size) + size)
	{
		x = (p.x * size) - 1;
		while (++x <= (p.x * size) + size)
		{
			img_pixel_put(img, (t_icoords){.x = x + offset, .y = y + offset}, \
				color);
		}
	}
}

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

static void	loop_vertically(t_cub *cub, int size, int offset)
{
	t_icoords	loop;
	t_icoords	player;
	int			color;

	player.x = cub->player.pos.x / CUB_SIZE;
	player.y = cub->player.pos.y / CUB_SIZE;
	loop.y = player.y;
	while (loop.y >= 0 && player.y - loop.y <= 6)
	{
		loop.x = player.x;
		while (--loop.x >= 0 && player.x - loop.x <= 5)
		{
			color = 0xFFFFFF;
			if (cub->input.map_arr[loop.y][loop.x] == '1')
				color = 0x303030;
			else if (cub->input.map_arr[loop.y][loop.x] == ' ')
				color = 0;
			draw_object_square((t_icoords){.x = abs(loop.x - player.x), \
				.y = loop.y}, &cub->display.img, color, size / 11, offset);
		}
		loop.y--;
	}

}

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

static void	draw_minimap_objects(t_cub *cub, int scale, int offset)
{
	//t_icoords	loop;
	//int			color;
	int			size;

	size = WIN_HEIGHT / scale;
	loop_vertically(cub, size, offset);
	// loop.y = -1;
	// while (cub->input.map_arr[++loop.y])
	// {
	// 	loop.x = -1;
	// 	while (cub->input.map_arr[loop.y][++loop.x])
	// 	{
	// 		color = 0xF0F0F0;
	// 		if (cub->input.map_arr[loop.y][loop.x] == ' ')
	// 			continue ;
	// 		else if (cub->input.map_arr[loop.y][loop.x] == '1')
	// 			color = 0x3F3F3F;
	// 		draw_object_square(loop, &cub->display.img, color, size / 11, \
	// 			offset);
	// 	}
	// }
}

/* -------------------------------------------------------------------------- */

void	draw_minimap(t_cub *cub)
{
	int scale;
	int	offset;

	scale = 4;
	offset = (WIN_HEIGHT / scale) / 30;
	draw_minimap_base(cub, scale, offset);
	draw_minimap_objects(cub, scale, offset);
	draw_minimap_player(cub, scale);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
