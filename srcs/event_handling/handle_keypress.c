/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:12:18 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/14 21:21:46 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -------------------------------------------------------------------------- */

static int	close_window(void *v_cub)
{
	t_cub	*cub;

	cub = (t_cub *)v_cub;
	ft_free_2d_char_arr(cub->input.map_arr);
	mlx_destroy_image(cub->display.mlx, cub->display.img.img_ptr);
	mlx_destroy_window(cub->display.mlx, cub->display.win);
	return (exit(0), 0);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

static int	key_press(int keycode, void *v_cub)
{
	t_cub	*cub;

	cub = (t_cub *)v_cub;
	if (keycode == KEY_ESCAPE)
		return (close_window(v_cub));
	else if (keycode == KEY_RIGHT)
		cub->player.turn_dir = 1;
	else if (keycode == KEY_LEFT)
		cub->player.turn_dir = -1;
	else if (keycode == KEY_W || keycode == KEY_UP)
		cub->player.walk_dir = 1;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		cub->player.walk_dir = -1;
	else if (keycode == KEY_D)
		cub->player.walk_horizon = 1;
	else if (keycode == KEY_A)
		cub->player.walk_horizon = -1;
	return (0);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

static int	key_release(int keycode, t_cub *v_cub)
{
	t_cub	*cub;

	cub = (t_cub *)v_cub;
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_UP || \
		keycode == KEY_DOWN)
		cub->player.walk_dir = 0;
	else if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		cub->player.turn_dir = 0;
	else if (keycode == KEY_D || keycode == KEY_A)
		cub->player.walk_horizon = 0;
	return (0);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void	handle_keys(t_cub *cub)
{
	t_display	*disp;

	disp = &cub->display;
	mlx_hook(disp->win, KEY_PRESS, KP_MASK, &key_press, (void *)cub);
	mlx_hook(disp->win, KEY_RELEASE, KR_MASK, &key_release, (void *)cub);
	mlx_hook(disp->win, DESTROY_NOTIFY, NO_MASK, &close_window, (void *)cub);
	mlx_hook(disp->win, MOUSE_CLICK, (1 << 8), &mouse_click, (void *)cub);
	mlx_hook(disp->win, MOUSE_RELEASE, (1 << 8), &mouse_release, (void *)cub);
	mlx_hook(disp->win, MOUSE_MOVEMENT, (1 << 6), &mouse_hover, (void *)cub);
	mlx_loop_hook(disp->mlx, &draw_and_output_image, (void *)cub);
}
