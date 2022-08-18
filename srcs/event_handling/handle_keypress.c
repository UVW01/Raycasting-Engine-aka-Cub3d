#include "../cub3d.h"

void    player_movement(int keycode, t_cub *cub)
{
    if (keycode == KEY_UP || keycode == KEY_W)
        cub->player.position.y--;
    else if (keycode == KEY_DOWN || keycode == KEY_S)
        cub->player.position.y++;
    else if (keycode == KEY_LEFT || keycode == KEY_A)
        cub->player.position.x--;// we'll update this line degree of rotaion later
    else if (keycode == KEY_RIGHT || keycode == KEY_D)
        cub->player.position.x++;// we'll update this line degree of rotaion later
    // printf("PlayerX:%d\nPlayerY:%d\n\n", cub->player.position.x, cub->player.position.y);
}

/* -- Notes: ----------------------------------------------------------------/ /
/ /------------------------------------------------------------------------- */

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

int key_press(int keycode, void *_cub)
{
    t_cub   *cub;

    cub = (t_cub *)_cub;
    player_movement(keycode, cub);
    esc_close(keycode, cub);
    return (0);
}
