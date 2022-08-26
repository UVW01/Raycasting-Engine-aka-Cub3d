/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line_algo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:12:18 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/14 21:21:46 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -------------------------------------------------------------------------- */

void	img_pixel_put(t_img *img, t_icoords pxl, int color)
{
	char	*pxl_ptr;

	if ((pxl.x >= 0 && pxl.x < WIN_WIDTH) && (pxl.y >= 0 && pxl.y < WIN_HEIGHT))
	{
		pxl_ptr = img->addr;
		pxl_ptr += pxl.y * img->line_length;
		pxl_ptr += pxl.x * (img->bits_per_pixel / 8);
		*(t_uint *)pxl_ptr = color;
	}
}

/* -------------------------------------------------------------------------- */

static void	dl_continued(t_img *img, t_icoords p1, int color, t_brsnhm brsnhm)
{
	while (brsnhm.pxl.x != p1.x || brsnhm.pxl.y != p1.y)
	{
		img_pixel_put(img, brsnhm.pxl, color);
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

void	draw_line(t_img *img, t_fcoords fp0, t_fcoords fp1, int color)
{
	t_brsnhm	brsnhm;
	t_icoords	p0;
	t_icoords	p1;

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
	dl_continued(img, p1, color, brsnhm);
}
