/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:12:18 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/14 21:21:46 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -- Notes: ----------------------------------------------------------------/ /
/ /------------------------------------------------------------------------- */

void	draw_background(t_img *img, t_input *input)
{
	int	y0;
	int	y1;

	y0 = 0;
	y1 = WIN_HEIGHT / 2;
	while (y0 <= y1)
	{
		draw_line(img, (t_coords){.x = 0, .y = y0}, \
			(t_coords){.x = WIN_WIDTH, .y = y0}, input->ceil_clr);
		++y0;
	}
	y0 = WIN_HEIGHT / 2;
	y1 = WIN_HEIGHT;
	while (y0 <= y1)
	{
		draw_line(img, (t_coords){.x = 0, .y = y0},	\
			(t_coords){.x = WIN_WIDTH, .y = y0}, input->floor_clr);
		++y0;
	}
}
