/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:32:06 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/16 10:34:36 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -------------------------------------------------------------------------- */

static void	error_check_colors(char *a_rgb)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (a_rgb[++i])
	{
		if (!ft_isdigit(a_rgb[i]) && a_rgb[i] != ',')
			ft_perror(MAP_ERR"Invalid Color code", 1);
		if (a_rgb[i] == ',' && count < 2)
			count++;
		else if (a_rgb[i] == ',' && count >= 2)
			ft_perror(MAP_ERR"Invalid color format", 1);
	}
}

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

void	check_init_color(char **line_split, t_input *gen_data)
{
	int		i;
	int		*clr;
	int		tmp_clr;
	char	**a_rgb;

	i = 0;
	clr = NULL;
	error_check_colors(line_split[1]);
	a_rgb = ft_split(line_split[1], ',');
	if (a_rgb[3] != NULL)
		ft_perror(MAP_ERR"Too many color values", 1);
	if (!ft_strcmp(line_split[0], "C"))
		clr = &gen_data->ceil_clr;
	else if (!ft_strcmp(line_split[0], "F"))
		clr = &gen_data->floor_clr;
	if (*clr != -1)
		ft_perror(MAP_ERR"Color redefinition", 1);
	*clr = 0;
	while (a_rgb[i])
	{
		tmp_clr = ft_atoi(a_rgb[i]);
		if (ft_strlen(a_rgb[i]) > 3 || tmp_clr > 255)
			ft_perror(MAP_ERR"Color code out of range", 1);
		*clr |= tmp_clr;
		if (i++ < 2)
			(*clr) <<= 8;
	}
	ft_free_2d_char_arr(a_rgb);
}

/* -------------------------------------------------------------------------- */

static void	init_texture_imgs(int dirctn, t_input *gen_data, void *img_ptr)
{
	if (gen_data->texture_imgs[dirctn] != NULL)
		ft_perror(MAP_ERR"Texture redefinition", 1);
	gen_data->texture_imgs[dirctn] = img_ptr;
}

/* -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  */

void	check_init_direction_texture(char **line_split, t_input *gen_data, \
	void *mlx)
{
	void		*img_ptr;
	t_icoords	dimensions;

	dimensions = (t_icoords){.x = CUB_SIZE, .y = CUB_SIZE};
	img_ptr = mlx_xpm_file_to_image(mlx, line_split[1], &dimensions.x, \
		&dimensions.y);
	if (img_ptr == NULL)
		ft_perror(FD_ERR, 1);
	if (!ft_strcmp(line_split[0], "NO"))
		init_texture_imgs(NO, gen_data, img_ptr);
	else if (!ft_strcmp(line_split[0], "SO"))
		init_texture_imgs(SO, gen_data, img_ptr);
	else if (!ft_strcmp(line_split[0], "WE"))
		init_texture_imgs(WE, gen_data, img_ptr);
	else if (!ft_strcmp(line_split[0], "EA"))
		init_texture_imgs(EA, gen_data, img_ptr);
}
