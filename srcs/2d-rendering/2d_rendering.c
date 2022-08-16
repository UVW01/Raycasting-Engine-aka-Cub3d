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
    int x_square;
    int y_square;

    cub->map_img.img = mlx_new_image(cub->win.mlx, WIN_WIDTH, WIN_HEIGHT);// creating 2d map img
    cub->map_img.addr = mlx_get_data_addr(cub->map_img.img, &cub->map_img.bits_per_pixel, &cub->map_img.line_length, &cub->map_img.endian);// getting img atterbutes

    x_square = (WIN_WIDTH / get_longest_grid(cub->gen_data.map_arr));// gonna use it later
    y_square = (WIN_HEIGHT / get_longest_grid(cub->gen_data.map_arr));// gonna use it later
    i = 0;
    while(cub->gen_data.map_arr[i])
    {
        j = 0;
        while(cub->gen_data.map_arr[i][j])
        {
            color = 0x2DC7EF;
            if (cub->gen_data.map_arr[i][j] == '0' || ft_strchr("NSWE", cub->gen_data.map_arr[i][j]))
                color = 0x4D0244;
            else if (cub->gen_data.map_arr[i][j] == ' ')
                color = 0x000000;
            draw_box(j * 15, i * 15, color, &cub->map_img);
            j++;
        }
        i++;
    }
    mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->map_img.img, 0, 0);
}

/* -- Notes: this used to render/draw player poind to map */
/* -------------------------------------------------------------------------- */

void    render_player(t_cub *cub)//for drawing player point in the window
{
    int i;
    int j;
    int color;
    int x_square;
    int y_square;

    // cub->player_img.img = mlx_new_image(cub->win.mlx, 3, 3);//init player img
    // cub->player_img.addr = mlx_get_data_addr(cub->player_img.img, &cub->player_img.bits_per_pixel, &cub->player_img.line_length, &cub->player_img.endian);// getting img atterebutes

    cub->player_img.img = mlx_xpm_file_to_image(cub->win.mlx, "eye.xpm",
        &cub->player_img.img_width, &cub->player_img.img_height);
    x_square = (WIN_WIDTH / get_longest_grid(cub->gen_data.map_arr));// gonna use it later
    y_square = (WIN_HEIGHT / get_longest_grid(cub->gen_data.map_arr));// gonna use it later
    i = 0;
    while(cub->gen_data.map_arr[i])
    {
        j = 0;
        while(cub->gen_data.map_arr[i][j])
        {
            color = 0xDE0F17;
            if (ft_strchr("NSWE", cub->gen_data.map_arr[i][j]))
                mlx_put_image_to_window(cub->win.mlx, cub->win.win, cub->player_img.img, (j * 15) + cub->player.x, (i * 15) + cub->player.y);
            j++;
        }
        i++;
    }
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
	render_player(cub);
	return (0);
}

/* -- Notes: this used to call all above functions taht's it */
/* -------------------------------------------------------------------------- */

void towD_rendering(t_cub *cub)
{
    cub->player.x = 1;
    cub->player.y = 1;

    render_2d(cub);
    render_player(cub);
    mlx_hook(cub->win.win, 2, 1L<<0, player_move, cub);
}
