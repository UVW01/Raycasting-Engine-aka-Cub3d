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

static void	draw_square(t_img *img, t_coords sq_center, int size, int clr)
{
	t_coords	pxl;

	pxl.x = sq_center.x - (size / 2);
	pxl.y = sq_center.y - (size / 2);
	while (pxl.y++ <= sq_center.y + (size / 2))
		draw_line(img, pxl, (t_coords){.x = (pxl.x + size), .y = pxl.y}, clr);
}

/* -------------------------------------------------------------------------- */

static void	draw_rows(t_img *img, char *map_row, t_coords square, int size)
{
	int	color;
	int	x;

	x = 0;
	while (map_row[x])
	{
		color = 0xc9c9c7;
		if (map_row[x] == '1')
			color = 0x4f2607;
		else if (map_row[x] == ' ')
			color = 0x2b2b2b;
		draw_square(img, square, size, color);
		if (ft_strchr("NEWS", map_row[x]))
			draw_square(img, square, size / 4, 0x053ea1);
		square.x += size;
		++x;
	}
}

/* -------------------------------------------------------------------------- */

void	draw_minimap(t_img *img, char **map_arr, int size, t_coords start)
{
	t_coords	square;
	int			y;

	y = 0;
	square.y = start.y + (size / 2);
	while (map_arr[y])
	{
		square.x = start.x + (size / 2);
		draw_rows(img, map_arr[y], square, size);
		square.y += size;
		++y;
	}
}
