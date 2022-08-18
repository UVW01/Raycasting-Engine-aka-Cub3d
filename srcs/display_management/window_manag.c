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

void	reset_window(void *mlx, void *win, t_img *img)
{
	mlx_clear_window(mlx, win);
	mlx_destroy_image(mlx, img->img_ptr);
	img->img_ptr = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
}

/* -- Notes: ----------------------------------------------------------------/ /
/ /------------------------------------------------------------------------- */

// static int	xclose(void *v_cub)
// {
// 	t_cub	*cub;

// 	cub = (t_cub *)v_cub;
// 	ft_free_2d_char_arr(cub->input.map_arr);
// 	mlx_destroy_image(cub->display.mlx, cub->display.img.img_ptr);
// 	mlx_destroy_window(cub->display.mlx, cub->display.win);
// 	return (exit(0), 0);
// }

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
	t_coords	minimap;

	disp = &cub->display;
	init_mlx_params(disp);
	minimap.x = 25;
	minimap.y = 25;
	draw_background(&cub->display.img, &cub->input);
	draw_minimap(&cub->display.img, cub->input.map_arr, 15, minimap);
	mlx_put_image_to_window(disp->mlx, disp->win, disp->img.img_ptr, 0, 0);
	mlx_hook(disp->win, KEY_PRESS, NO_EVENT_MASK, NULL, (void *)cub);
	//mlx_hook(disp->win, DESTROY_NOTIFY, NO_EVENT_MASK, &xclose, (void *)cub);
	mlx_loop(disp->mlx);
}
