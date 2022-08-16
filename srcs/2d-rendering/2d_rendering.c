#include "../cub3d.h"
/* -- Notes: it just getting the how long the x cordonets of the map then
             this used to resize each pixil to make the map fit window width.
             It's not used now but we can use it later, it tested and it works
             well
 */
/* -------------------------------------------------------------------------- */
int get_longest_grid(char **arr)
{
    int i;
    int len;
    int tmp;

    i = 0;
    len = 0;
    tmp = 0;
    while(arr[i])
    {
        tmp = ft_strlen(arr[i]);
        if (tmp > len)
            len = tmp;
        i++;
    }
    return (len);
}

/* -- Notes:this used to render/draw map to window*/
/* -------------------------------------------------------------------------- */

void    render_2d(t_cub *cub)
{
    int i;
    int j;
    int color;
    int x_player;
    int y_player;

    cub->map_img.img = mlx_new_image(cub->win.mlx, WIN_WIDTH, WIN_HEIGHT);// creating 2d map img
    cub->map_img.addr = mlx_get_data_addr(cub->map_img.img, \
        &cub->map_img.bits_per_pixel, &cub->map_img.line_length, \
        &cub->map_img.endian);// getting img atterbutes
    i = 0;
    while(cub->gen_data.map_arr[i])
    {
        j = 0;
        while(cub->gen_data.map_arr[i][j])
        {
            color = 0x2DC7EF;
            if (cub->gen_data.map_arr[i][j] == '0')
                color = 0x4D0244;
            else if (cub->gen_data.map_arr[i][j] == ' ')
                color = 0x000000;
            if (ft_strchr("NSWE", cub->gen_data.map_arr[i][j]))
            {
                color = 0x4D0244;
                x_player = (j * 20);
                y_player = (i * 20);
            }
            draw_box(j * 20, i * 20, color, &cub->map_img);
            j++;
        }
        i++;
    }
    draw_player(x_player + cub->player.x, y_player + cub->player.y, 0xff6a00, &cub->map_img);
    mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->map_img.img, 0, 0);
}

/* -- Notes: this used to render/draw player poind to map */
/* -------------------------------------------------------------------------- */

void    render_player(t_cub *cub)//for drawing player point in the window
{
    // player stuff will be added here
}

/* -- Notes: used to handel movement of the player when a user pressed a key */
/* -------------------------------------------------------------------------- */

int	player_move(int keycode, t_cub *cub) // This stuff not working well
{
    int x;
    int y;

    x = 1;
    y = 1;
	if (keycode == 126)
        cub->player.y--;
    else if (keycode == 125)
        cub->player.y++;
    mlx_destroy_image(cub->win.mlx, cub->map_img.img);
	render_2d(cub);
	return (0);
}

/* -- Notes: this used to call all above functions taht's it */
/* -------------------------------------------------------------------------- */

void towD_rendering(t_cub *cub)
{
    cub->player.x = 1;
    cub->player.y = 1;

    render_2d(cub);
    mlx_hook(cub->win.win, 2, 1L<<0, player_move, cub);
}
