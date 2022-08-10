/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:03:20 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/10 18:52:54 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_init_color(char **line_split, t_gen_data *gen_data)
{
	char	**a_rgb;
	int		i;
	int		j;

	a_rgb = ft_split(line_split[1], ',');
	if (a_rgb[3] != NULL)
		ft_perror(MAP_ERR, 1);
	i = -1;
	while (a_rgb[++i])
	{
		if (ft_strlen(a_rgb[i]) > 3 || ft_strlen(a_rgb[i]) == 0)
			ft_perror(MAP_ERR, 1);
		j = -1;
		while (a_rgb[i][++j])
			if (!ft_isdigit(a_rgb[i][j]))
				ft_perror(MAP_ERR, 1);
	}
}

/* -- Notes: ---------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

void	init_default_values(t_gen_data *gen_data)
{
	gen_data->texture_fds[0] = -69;
	gen_data->texture_fds[1] = -69;
	gen_data->texture_fds[2] = -69;
	gen_data->texture_fds[3] = -69;
	gen_data->ceil_clr = -1;
	gen_data->floor_clr = -1;
	gen_data->map_arr = NULL;
}

/* -- Notes: ---------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

void	init_texture_fds(int dirctn, t_gen_data *gen_data, int fd)
{
	if (gen_data->texture_fds[dirctn] != -69)
		ft_perror(MAP_ERR, 1);
	gen_data->texture_fds[dirctn] = fd;
}

/* -- Notes: ---------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

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

/* -- Notes: ---------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

void	check_and_init_data(char *line, t_gen_data *gen_data)
{
	char	**line_split;

	line_split = ft_split(line, ' ');
	if (line_split[2] != NULL || ft_strlen(line_split[0]) > 2)
		ft_perror(MAP_ERR, 1);
	if (ft_strstr(MAP_DIRECTNS, line_split[0]))
		check_init_direction_texture(line_split, gen_data);
	else if (!ft_strcmp(line_split[0], "F") || !ft_strcmp(line_split[0], "C"))
		check_init_color(line_split, gen_data);
	else
		ft_perror(MAP_ERR, 1);
		
}

/* -- Notes: ---------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

int	process_file_data(char *filename, t_gen_data *gen_data)
{
	int		map_fd;
	char	*line;

	init_default_values(gen_data);
	map_fd = open(filename, O_RDONLY);
	if (map_fd < 0)
		ft_perror(FD_ERR, 1);
	line = get_next_line(map_fd, 1);
	if (line == NULL)
		ft_perror(EMPTY_FL_ERR, 1);
	while (line != NULL)
	{
		if (line[0] != '\n')
			check_and_init_data(line, gen_data);
		free(line);
		line = get_next_line(map_fd, 1);
	}
	close(map_fd);
	return (EXIT_SUCCESS);
}

