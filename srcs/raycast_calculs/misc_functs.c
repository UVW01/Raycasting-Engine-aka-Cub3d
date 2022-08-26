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
    int exactX = floor(x / CUB_SIZE);
    int exactY = floor(y / CUB_SIZE);
    // if ((x < 0 || x > WIN_WIDTH) || (y < 0 || y > WIN_HEIGHT))
    //     return (true);
   
        printf("+++++++++ X:%d Y:%d +++++++\n", exactX, exactY);
        // printf("\n");

    if (map_arr[exactY][exactX] == '1')
    {

        printf("hasWallAt|X:%d| |Y:%d|\n", exactX, exactY);
        return (true);
    }
    return (false);
}
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
