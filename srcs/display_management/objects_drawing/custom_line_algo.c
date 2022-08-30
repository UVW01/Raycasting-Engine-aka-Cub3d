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

static void	dll_continued(t_img *img, t_icoords p1, int color, t_brsnhm brsnhm)
{
	(void)color;
	while (brsnhm.pxl.x != p1.x || brsnhm.pxl.y != p1.y)
	{
		if (brsnhm.pxl.x > img->m_offset && brsnhm.pxl.y > img->m_offset \
			&& brsnhm.pxl.x <= (WIN_HEIGHT / 4) - img->m_offset \
			&& brsnhm.pxl.y <= (WIN_HEIGHT / 4) - img->m_offset)
			img_pixel_put(img, brsnhm.pxl, color);
		else
			break ;
		brsnhm.e2 = 2 * brsnhm.err;
		if (brsnhm.e2 >= brsnhm.dlta.y)
		{
			brsnhm.err += brsnhm.dlta.y;
			brsnhm.pxl.x += brsnhm.s.x;
		}
		if (brsnhm.e2 <= brsnhm.dlta.x)
		{
			brsnhm.err += brsnhm.dlta.x;
			brsnhm.pxl.y += brsnhm.s.y;
		}
	}
}

/* -------------------------------------------------------------------------- */

void	draw_limited_line(t_cub *cub, t_fcoords fp0, t_fcoords fp1, int color)
{
	t_brsnhm	brsnhm;
	t_icoords	p0;
	t_icoords	p1;
	t_img	*img;

	img = &cub->display.img;
	p0 = (t_icoords){.x = (int)fp0.x, .y = (int)fp0.y};
	p1 = (t_icoords){.x = (int)fp1.x, .y = (int)fp1.y};
	brsnhm.dlta.x = abs(p1.x - p0.x);
	brsnhm.dlta.y = -abs(p1.y - p0.y);
	brsnhm.s.x = -1;
	if (p0.x < p1.x)
		brsnhm.s.x = 1;
	brsnhm.s.y = -1;
	if (p0.y < p1.y)
		brsnhm.s.y = 1;
	brsnhm.err = brsnhm.dlta.x + brsnhm.dlta.y;
	brsnhm.pxl = (t_icoords){.x = p0.x, .y = p0.y};
	dll_continued(img, p1, color, brsnhm);
}
