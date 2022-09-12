/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_line_algo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:12:18 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/14 21:21:46 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

static	void	dda_util(t_fcoords p0, t_fcoords p1, int *steps, t_fcoords *inc)
{
	int	dx;
	int	dy;

	dx = ((int)p1.x - (int)p0.x);
	dy = ((int)p1.y - (int)p0.y);
	if (abs(dx) > abs(dy))
		*steps = abs(dx);
	else
		*steps = abs(dy);
	inc->x = (dx / (float)*steps);
	inc->y = (dy / (float)*steps);
}

void	draw_limited_line(t_cub *cub, t_fcoords p0, t_fcoords p1, int color)
{
	int			steps;
	t_fcoords	inc;
	int			i;
	t_fcoords	new_pos;

	i = 0;
	dda_util(p0, p1, &steps, &inc);
	new_pos.x = (int)p0.x;
	new_pos.y = (int)p0.x;
	while (i <= steps)
	{
		if (new_pos.x > cub->display.img.m_offset \
			&& new_pos.y > cub->display.img.m_offset \
			&& new_pos.x <= (WIN_HEIGHT / 4) - cub->display.img.m_offset \
			&& new_pos.y <= (WIN_HEIGHT / 4) - cub->display.img.m_offset)
			img_pixel_put(&cub->display.img,
				(t_icoords){.x = new_pos.x, .y = new_pos.y}, color);
		new_pos.x += inc.x;
		new_pos.y += inc.y;
		i++;
	}
}
