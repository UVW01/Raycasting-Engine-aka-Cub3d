/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parcer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:03:20 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/16 10:51:38 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -------------------------------------------------------------------------- */

static char	**split_args(char *line)
{
	char	*arg;
	char	**args;
	void	*ptr;

	arg = ft_strchr(line, ' ');
	if (arg == NULL)
		return (NULL);
	args = (char **)ft_calloc(3, sizeof(char *));
	args[0] = ft_substr(line, 0, arg - line);
	args[1] = ft_strdup(arg + 1);
	if (args[0] == NULL || args[1] == NULL)
		ft_perror(GEN_ERR, 1);
	ptr = args[1];
	args[1] = ft_strtrim(args[1], " ");
	free(ptr);
	return (args);
}

/* -------------------------------------------------------------------------- */

static void	check_and_init_data(char *line, t_input *data, void *mlx)
{
	char	**line_split;

	line_split = split_args(line);
	if (line_split == NULL || ft_strlen(line_split[0]) > 2)
		ft_perror(MAP_ERR"Too many values", 1);
	if (ft_strstr(MAP_DIRECTNS, line_split[0]))
		check_init_texture(line_split, data, mlx);
	else if (!ft_strcmp(line_split[0], "F") || !ft_strcmp(line_split[0], "C"))
		check_init_color(line_split, data);
	else
		ft_perror(MAP_ERR"Invalid map elements", 1);
	ft_free_2d_char_arr(line_split);
}

/* -------------------------------------------------------------------------- */

static void	init_default_values(t_input *data, bool *mp_obj_found)
{
	ft_bzero(&data->textures[NO], sizeof(t_img));
	ft_bzero(&data->textures[SO], sizeof(t_img));
	ft_bzero(&data->textures[EA], sizeof(t_img));
	ft_bzero(&data->textures[WE], sizeof(t_img));
	data->ceil_clr = -1;
	data->floor_clr = -1;
	data->map_arr = NULL;
	*mp_obj_found = false;
}

/* -------------------------------------------------------------------------- */

static void	check_other_factors(t_cub *cub)
{
	map_is_closed(cub->input.map_arr);
	only_one_player(cub->input.map_arr, &cub->player);
	place_virtual_walls(cub->input.map_arr);
	if (cub->input.textures[NO].img_ptr == NULL || \
		cub->input.textures[SO].img_ptr == NULL || \
		cub->input.textures[EA].img_ptr == NULL || \
		cub->input.textures[WE].img_ptr == NULL || \
		cub->input.ceil_clr == -1 || \
		cub->input.floor_clr == -1)
		ft_perror("Missing data", 1);
}

/* -------------------------------------------------------------------------- */

void	process_file_data(char *filename, t_cub *cub)
{
	bool	mp_obj_found;
	int		map_fd;
	char	*line;

	init_default_values(&cub->input, &mp_obj_found);
	map_fd = open(filename, O_RDONLY);
	if (map_fd < 0)
		ft_perror(FD_ERR, 1);
	line = get_next_line(map_fd, 1);
	if (line == NULL)
		ft_perror(EMPTY_FL_ERR, 1);
	while (line != NULL)
	{
		if (line[0] && is_map_objs(line, &mp_obj_found))
			process_map_arr(&cub->input, line);
		else if (line[0] && mp_obj_found == false)
			check_and_init_data(line, &cub->input, cub->display.mlx);
		else if (line[0] && mp_obj_found == true)
			ft_perror(MAP_ERR, 1);
		free(line);
		line = get_next_line(map_fd, 1);
	}
	check_other_factors(cub);
	close(map_fd);
}
