/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_keypress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:12:18 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/14 21:21:46 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

int	mouse_hover(int x, int y, void *v_cub)
{
	t_cub	*cub;

	(void)y;
	cub = (t_cub *)v_cub;
	if (!cub->player.mouse_click)
		return (0);
	else if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		if (x > cub->player.mouse_prev_x)
			cub->player.rot += deg2rad(3);
		else if (x < cub->player.mouse_prev_x)
			cub->player.rot -= deg2rad(3);
		normalize_angle(cub->player.rot);
		cub->player.mouse_prev_x = x;
	}
	return (0);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

int	mouse_click(int keycode, int x, int y, void *v_cub)
{
	t_cub	*cub;

	(void)keycode;
	cub = (t_cub *)v_cub;
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		cub->player.mouse_prev_x = x;
		cub->player.mouse_click = 1;
	}
	return (0);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

int	mouse_release(int keycode, int x, int y, void *v_cub)
{
	t_cub	*cub;

	(void)keycode;
	(void)x;
	(void)y;
	cub = (t_cub *)v_cub;
	cub->player.mouse_click = 0;
	return (0);
}
