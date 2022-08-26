/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:12:18 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/14 21:21:46 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -------------------------------------------------------------------------- */

void	reset_window(t_cub *cub)
{
	mlx_clear_window(cub->display.mlx, cub->display.win);
	mlx_destroy_image(cub->display.mlx, cub->display.img.img_ptr);
	cub->display.img.img_ptr = mlx_new_image(cub->display.mlx, WIN_WIDTH, \
		WIN_HEIGHT);
	cub->display.img.addr = mlx_get_data_addr(cub->display.img.img_ptr, \
		&cub->display.img.bits_per_pixel, &cub->display.img.line_length, \
		&cub->display.img.endian);
}

/* -------------------------------------------------------------------------- */

static void	init_minilibx_parameters(t_display *disp, t_cub *cub)
{
	t_img	*img;

	disp->mlx = mlx_init();
	if (disp->mlx == NULL)
		ft_perror(MLX_ERR, 1);
	disp->win = mlx_new_window(disp->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (disp->win == NULL)
		ft_perror(WIN_ERR, 1);
	img = &disp->img;
	img->img_ptr = mlx_new_image(disp->mlx, WIN_WIDTH, WIN_HEIGHT);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
	mlx_hook(disp->win, KEY_PRESS, NO_EVENT_MASK, &key_press, (void *)cub);
	mlx_hook(disp->win, DESTROY_NOTIFY, NO_EVENT_MASK, &xclose, (void *)cub);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void	init_display_params(t_cub *cub)
{
	t_display	*disp;

	disp = &cub->display;
	init_minilibx_parameters(disp, cub);
	// Reconsider the following
	draw_minimap(cub);
	update_player_position(cub);
	casting_rays(cub);
	draw_player(&cub->player, &cub->display.img, (CUB_SIZE / 10));
	// ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
	mlx_put_image_to_window(disp->mlx, disp->win, disp->img.img_ptr, 0, 0);
	mlx_loop(disp->mlx);
}

/* -------------------------------------------------------------------------- */

