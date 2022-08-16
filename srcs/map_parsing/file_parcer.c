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

/* -- Notes: ----------------------------------------------------------------/ /
/ /------------------------------------------------------------------------- */

static void	check_and_init_data(char *line, t_input *data)
{
	char	**line_split;

	line_split = ft_split(line, ' ');
	if (line_split[2] != NULL || ft_strlen(line_split[0]) > 2)
		ft_perror(MAP_ERR"Too many values", 1);
	if (ft_strstr(MAP_DIRECTNS, line_split[0]))
		check_init_direction_texture(line_split, data);
	else if (!ft_strcmp(line_split[0], "F") || !ft_strcmp(line_split[0], "C"))
		check_init_color(line_split, data);
	else
		ft_perror(MAP_ERR"Invalid map elements", 1);
	ft_free_2d_char_arr(line_split);
}

/* -- Notes: ----------------------------------------------------------------/ /
/ /------------------------------------------------------------------------- */

static bool	is_map_objs(char *line, bool *is_mp_obj)
{
	char	*tmp;

	tmp = ft_strtrim(line, MAP_OBJS);
	if (tmp[0] == '\0')
	{
		*is_mp_obj = true;
		return (free(tmp), true);
	}
	return (free(tmp), false);
}

/* -- Notes: ----------------------------------------------------------------/ /
/ /------------------------------------------------------------------------- */

static void	process_map_arr(t_input *data, char *line)
{
	char	**tmp_arr;
	int		i;

	i = 0;
	while (data->map_arr && data->map_arr[i])
		++i;
	tmp_arr = (char **)ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (data->map_arr && data->map_arr[i])
	{
		tmp_arr[i] = data->map_arr[i];
		++i;
	}
	tmp_arr[i] = ft_strdup(line);
	free(data->map_arr);
	data->map_arr = tmp_arr;
}

/* -- Notes: ----------------------------------------------------------------/ /
/ /------------------------------------------------------------------------- */

static void	init_default_values(t_input *data, bool *mp_obj_found)
{
	data->texture_fds[0] = -69;
	data->texture_fds[1] = -69;
	data->texture_fds[2] = -69;
	data->texture_fds[3] = -69;
	data->ceil_clr = -1;
	data->floor_clr = -1;
	data->map_arr = NULL;
	*mp_obj_found = false;
}

/* -- Notes: ----------------------------------------------------------------///
I have modified the get_next_line function so that it trims the trailing 
newline '\n' character, it is more convinient than triming it later with 
'ft_strtrim', it just lowers the code's complexity
///-------------------------------------------------------------------------- */

void	process_file_data(char *filename, t_input *gen_data)
{
	bool	mp_obj_found;
	int		map_fd;
	char	*line;
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (ext == NULL || ft_strcmp(ext, ".cub"))
		ft_perror(EXT_ERR, 1);
	init_default_values(gen_data, &mp_obj_found);
	map_fd = open(filename, O_RDONLY);
	if (map_fd < 0)
		ft_perror(FD_ERR, 1);
	line = get_next_line(map_fd, 1);
	if (line == NULL)
		ft_perror(EMPTY_FL_ERR, 1);
	while (line != NULL)
	{
		if (line[0] && is_map_objs(line, &mp_obj_found))
			process_map_arr(gen_data, line);
		else if (line[0] && mp_obj_found == false)
			check_and_init_data(line, gen_data);
		else if (line[0] && mp_obj_found == true)
			ft_perror(MAP_ERR, 1);
		free(line);
		line = get_next_line(map_fd, 1);
	}
	map_is_closed(gen_data->map_arr);
	only_one_player(gen_data->map_arr);
	close(map_fd);
}
