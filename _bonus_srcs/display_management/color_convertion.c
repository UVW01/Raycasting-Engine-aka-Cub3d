/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_convertion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:12:18 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/14 21:21:46 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -------------------------------------------------------------------------- */

double	get_darkness_percent(double value, double max_value)
{
	double	percent;

	percent = 100 / (max_value / value);
	return (percent);
}

/* -------------------------------------------------------------------------- */

int	shade_color(int color, double percent)
{
	int	red;
	int	green;
	int	blue;

	red = color >> 16;
	red &= 255;
	green = color >> 8;
	green &= 255;
	blue = color;
	blue &= 255;
	red /= (100.0 + percent) / 100.0;
	green /= (100.0 + percent) / 100.0;
	blue /= (100.0 + percent) / 100.0;
	if (red > 255)
		red = 255;
	if (green > 255)
		green = 255;
	if (blue > 255)
		blue = 255;
	return (red << 16 | green << 8 | blue);
}
