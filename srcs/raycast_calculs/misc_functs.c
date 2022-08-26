/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_funct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:12:18 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/14 21:21:46 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -------------------------------------------------------------------------- */

float	deg2rad(int deg)
{
    return (deg * (M_PI / 180));
}

/* -------------------------------------------------------------------------- */

int	rad2deg(float rad)
{
    return (rad * (180 / M_PI));
}

/* -------------------------------------------------------------------------- */

float	normalize_angle(float rotation)
{
	rotation = fmodf(rotation, (M_PI * 2));
	if (rotation < 0)
		rotation += M_PI * 2;
	return (rotation);
}
/* -------------------------------------------------------------------------- */

bool    hasWallAtPos(char **map_arr, float x, float y)
{
    int exactX = (int)(x / CUB_SIZE);
    int exactY = (int)(y / CUB_SIZE);
    // if ((x < 0 || x > WIN_WIDTH) || (y < 0 || y > WIN_HEIGHT))
    //     return (true);
    if (map_arr[exactY][exactX] == '1')
        return (true);
    return (false);
}
/* -------------------------------------------------------------------------- */
double dstnce_btwn_points(float x1, float y1, float x2, float y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
/* -------------------------------------------------------------------------- */
