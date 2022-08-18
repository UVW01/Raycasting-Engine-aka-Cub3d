/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:53:32 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/16 10:59:16 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* -- Notes: ----------------------------------------------------------------/ /
/ /------------------------------------------------------------------------- */

void	init_mlx_params(t_display *display)
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

int	xclose(void *v_cub)
{
	t_cub	*cub;

	cub = (t_cub *)v_cub;
	ft_free_2d_char_arr(cub->input.map_arr);
	mlx_destroy_image(cub->display.mlx, cub->display.img.img_ptr);
	mlx_destroy_window(cub->display.mlx, cub->display.win);
	return (exit(0), 0);
}

/* -- Notes: ----------------------------------------------------------------/ /
/ /------------------------------------------------------------------------- */

void	init_display_params(t_cub *cub)
{
	t_display	*disp;

	disp = &cub->display;
	init_mlx_params(disp);
	draw_minimap(&cub->display.img, cub->input.map_arr, 15, (t_coords){.x = 25, .y = 25});
	mlx_put_image_to_window(disp->mlx, disp->win, disp->img.img_ptr, 0, 0);
	mlx_hook(disp->win, KEY_PRESS, NO_EVENT_MASK, NULL, (void *)cub);
	mlx_hook(disp->win, DESTROY_NOTIFY, NO_EVENT_MASK, &xclose, (void *)cub);
	mlx_loop(disp->mlx);
}

/* -- Notes: ----------------------------------------------------------------/ /
/ /------------------------------------------------------------------------- */

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
		return (EXIT_FAILURE);
	process_file_data(av[1], &cub.input);
	init_display_params(&cub);
	return (EXIT_SUCCESS);
}
