/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:32:06 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/12 20:28:06 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -- Notes: ---------------------------------------------------------------- */
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

void	check_init_color(char **line_split, t_gen_data *gen_data)
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

/* -- Notes: ---------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

static void	init_texture_fds(int dirctn, t_gen_data *gen_data, int fd)
{
	if (gen_data->texture_fds[dirctn] != -69)
		ft_perror(MAP_ERR"Texture redefinition", 1);
	gen_data->texture_fds[dirctn] = fd;
}

void	check_init_direction_texture(char **line_split, t_gen_data *gen_data)
{
	int	file_fd;

	file_fd = open(line_split[1], O_RDONLY);
	if (file_fd < 0)
		ft_perror(FD_ERR, 1);
	if (!ft_strcmp(line_split[0], "NO"))
		init_texture_fds(NO, gen_data, file_fd);
	else if (!ft_strcmp(line_split[0], "SO"))
		init_texture_fds(SO, gen_data, file_fd);
	else if (!ft_strcmp(line_split[0], "WE"))
		init_texture_fds(WE, gen_data, file_fd);
	else if (!ft_strcmp(line_split[0], "EA"))
		init_texture_fds(EA, gen_data, file_fd);
}
