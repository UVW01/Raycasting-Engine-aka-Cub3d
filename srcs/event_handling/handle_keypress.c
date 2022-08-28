
#include "../cub3d.h"

/* -------------------------------------------------------------------------- */

int	draw_and_output_image(t_cub *cub)
{
	reset_window(cub);
	draw_game_map(cub);
	update_player_position(cub);
	draw_player(&cub->player, &cub->display.img, (CUB_SIZE / 10));
	mlx_put_image_to_window(cub->display.mlx, cub->display.win,
		cub->display.img.img_ptr, 0, 0);
	return (0);
}

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

static int	key_press(int keycode, void *_cub)
{
	t_cub *cub;

	cub = (t_cub *)_cub;
	if (keycode == KEY_ESCAPE)
		return (close_window(_cub));
	else if (keycode == KEY_RIGHT)
		cub->player.turn_dir = 1;
	else if (keycode == KEY_LEFT)
		cub->player.turn_dir = -1;
	else if (keycode == KEY_W)
		cub->player.walk_dir = 1;
	else if (keycode == KEY_S)
		cub->player.walk_dir = -1;
	else if (keycode == KEY_D)
		cub->player.walk_horizon = 1;
	else if (keycode == KEY_A)
		cub->player.walk_horizon = -1;
	return (0);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

static int	key_release(int keycode, t_cub *cub)
{
	if (keycode == KEY_W || keycode == KEY_S)
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
	mlx_loop_hook(disp->mlx, &draw_and_output_image, (void *)cub);
}
