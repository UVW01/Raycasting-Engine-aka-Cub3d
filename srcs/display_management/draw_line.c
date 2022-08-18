/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
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

static void	img_pixel_put(t_img *img, t_coords pxl, int color)
{
	char	*pxl_ptr;

	if ((pxl.x >= 0 && pxl.x < WIN_WIDTH) && (pxl.y >= 0 && pxl.y < WIN_HEIGHT))
	{
		pxl_ptr = img->addr;
		pxl_ptr += pxl.y * img->line_length;
		pxl_ptr += pxl.x * (img->bits_per_pixel / 8);
		*(unsigned int *)pxl_ptr = color;
	}
}

/* -- Notes: ----------------------------------------------------------------/ /
/ /------------------------------------------------------------------------- */

static void	dl_continued(t_img *img, t_coords p1, int clr, t_brsnhm brsnhm)
{
	while (brsnhm.pxl.x != p1.x || brsnhm.pxl.y != p1.y)
	{
		img_pixel_put(img, brsnhm.pxl, clr);
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

/* -- Notes: ----------------------------------------------------------------/ /
/ /------------------------------------------------------------------------- */

void	draw_line(t_img *img, t_coords p0, t_coords p1, int clr)
{
	t_brsnhm	brsnhm;

	brsnhm.dlta.x = abs(p1.x - p0.x);
	brsnhm.dlta.y = -abs(p1.y - p0.y);
	brsnhm.s.x = -1;
	if (p0.x < p1.x)
		brsnhm.s.x = 1;
	brsnhm.s.y = -1;
	if (p0.y < p1.y)
		brsnhm.s.y = 1;
	brsnhm.err = brsnhm.dlta.x + brsnhm.dlta.y;
	brsnhm.pxl = p0;
	dl_continued(img, p1, clr, brsnhm);
}
