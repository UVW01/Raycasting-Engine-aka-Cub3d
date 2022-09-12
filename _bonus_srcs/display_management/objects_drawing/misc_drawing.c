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

	color = cub->input.ceil_clr;
	y = -1;
	while (++y < WIN_HEIGHT / 2)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			img_pixel_put(&cub->display.img, (t_icoords){.x = x, .y = y}, \
				color);
	}
	y = WIN_HEIGHT;
	while (--y > WIN_HEIGHT / 2)
	{
		x = -1;
		color = shade_color(cub->input.floor_clr, \
			get_darkness_percent(abs(y - WIN_HEIGHT), WIN_HEIGHT / 10));
		while (++x < WIN_WIDTH)
			img_pixel_put(&cub->display.img, (t_icoords){.x = x, .y = y}, \
				color);
	}
}
