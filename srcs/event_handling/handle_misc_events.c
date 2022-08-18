#include "../cub3d.h"

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
