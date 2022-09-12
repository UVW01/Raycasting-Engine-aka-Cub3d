/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing_algo.c                                :+:      :+:    :+:   */
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
