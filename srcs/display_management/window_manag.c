/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manag.c                                     :+:      :+:    :+:   */
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

void	reset_window(t_cub *cub)
{
	mlx_clear_window(cub->display.mlx, cub->display.win);
	mlx_destroy_image(cub->display.mlx, cub->display.img.img_ptr);
	cub->display.img.img_ptr = mlx_new_image(cub->display.mlx, WIN_WIDTH,\
		WIN_HEIGHT);
	cub->display.img.addr = mlx_get_data_addr(cub->display.img.img_ptr, \
		&cub->display.img.bits_per_pixel, &cub->display.img.line_length, \
		&cub->display.img.endian);
}

/* -- Notes: ----------------------------------------------------------------/ /
/ /------------------------------------------------------------------------- */

static void	init_mlx_params(t_display *display)
{
	display->mlx = mlx_init();
	if (!display->mlx)
		ft_perror(MLX_ERR, 1);
	display->win = mlx_new_window(display->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!display->win)
		ft_perror(WIN_ERR, 1);
	display->img.img_ptr = mlx_new_image(display->mlx, WIN_WIDTH, WIN_HEIGHT);
	display->img.addr = mlx_get_data_addr(display->img.img_ptr, \
		&display->img.bits_per_pixel, &display->img.line_length, \
		&display->img.endian);
}

/* -- Notes: ----------------------------------------------------------------/ /
/ /------------------------------------------------------------------------- */

void	init_display_params(t_cub *cub)
{
	t_display	*disp;

	disp = &cub->display;
	init_mlx_params(disp);
	draw_minimap(cub);
	update_player_position(&cub->player, &cub->display.img, cub->input.map_arr);
	casting_rays(cub);
	draw_player(cub->player.pos, &cub->display.img, (CUB_SIZE / 6));
	mlx_put_image_to_window(disp->mlx, disp->win, disp->img.img_ptr, 0, 0);
	mlx_hook(disp->win, KEY_PRESS, NO_EVENT_MASK, &key_press, (void *)cub);
	mlx_hook(disp->win, DESTROY_NOTIFY, NO_EVENT_MASK, &xclose, (void *)cub);
	mlx_loop(disp->mlx);
}
