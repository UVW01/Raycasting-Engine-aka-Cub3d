
#include "../cub3d.h"

/* -------------------------------------------------------------------------- */

void    redraw_and_output_image(t_cub *cub)
{
    reset_window(cub);
    draw_minimap(cub); 
	update_player_position(cub);
	draw_player(&cub->player, &cub->display.img, (CUB_SIZE / 10));
    mlx_put_image_to_window(cub->display.mlx, cub->display.win, \
        cub->display.img.img_ptr, 0, 0);
}

/* -------------------------------------------------------------------------- */

void    player_movement(int keycode, t_cub *cub)
{
    if (keycode == KEY_UP || keycode == KEY_W)
        cub->player.walk_dir = 1;
    else if (keycode == KEY_DOWN || keycode == KEY_S)
        cub->player.walk_dir = -1;
    else if (keycode == KEY_D)
        cub->player.turn_dir = 1;
    else if (keycode == KEY_A)
        cub->player.turn_dir = -1;
    else if (keycode == KEY_RIGHT)
        move_horizontally(cub, 1);
    else if (keycode == KEY_LEFT)
        move_horizontally(cub, -1);
    redraw_and_output_image(cub);
    cub->player.walk_dir = 0;
    cub->player.turn_dir = 0;
}

/* -------------------------------------------------------------------------- */

void	esc_close(int keycode, t_cub *cub)
{
    if (keycode == KEY_ESCAPE)
    {
        ft_free_2d_char_arr(cub->input.map_arr);
        mlx_destroy_image(cub->display.mlx, cub->display.img.img_ptr);
        mlx_destroy_window(cub->display.mlx, cub->display.win);
        exit(0);
    }
}

/* -------------------------------------------------------------------------- */

int key_press(int keycode, void *_cub)
{
    t_cub   *cub;

    cub = (t_cub *)_cub;
    player_movement(keycode, cub);
    esc_close(keycode, cub);
    return (0);
}
