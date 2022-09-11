/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_funct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <haitkadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:12:18 by haitkadi          #+#    #+#             */
/*   Updated: 2022/08/14 21:21:46 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -------------------------------------------------------------------------- */

double	deg2rad(int deg)
{
	return (deg * (M_PI / 180));
}

/* -------------------------------------------------------------------------- */

int	rad2deg(double rad)
{
	return (rad * (180 / M_PI));
}

/* -------------------------------------------------------------------------- */

double	normalize_angle(double rotation)
{
	rotation = fmodf(rotation, (M_PI * 2));
	if (rotation < 0)
		rotation += M_PI * 2;
	return (rotation);
}

/* -------------------------------------------------------------------------- */

double	dstnce_btwn_points(t_fcoords p, t_intrsctn intr)
{
	return (sqrt((intr.x_point - p.x) * (intr.x_point - p.x) + \
		(intr.y_point - p.y) * (intr.y_point - p.y)));
}
