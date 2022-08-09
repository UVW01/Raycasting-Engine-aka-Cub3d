/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:03:20 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/09 15:14:45 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -- Notes: ---------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

/* -- Notes: ---------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

bool	is_valid_map_line(char *line)
{
	char	*tmp_line;

	tmp_line = ft_strtrim(line, MAP_OBJS);
	if (tmp_line == NULL || tmp_line[0] != '\0')
		return (free(tmp_line), false);
	free(tmp_line);
	return (true);
}

/* -- Notes: ---------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

bool	is_valid_data(char **line, int8_t *elem_check)
{
	char	**elems_ids;
	int		i;
	
	i = -1;
	elems_ids = ft_split(MAP_ELEMENTS, ' ');
	while (++i < 8)
	{
		if (ft_strcmp(line[0], elems_ids[i]) == 0)
		{
			ft_free_2d_char_arr(elems_id);
			if (elem_check[i] == 0)
			{
				elem_check[i] = 1;
				return (true);
			}
			return (false);
		}
	}
	return (is_valid_map_line(line[0]));
}

/* -- Notes: ---------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

int	check_and_init_data(char *line, t_gen_data *gen_data, int8_t *elem_check)
{
	char	**sep_line;

	sep_line = ft_split(line, ' ');
	if (sep_line == NULL || *sep_line == '\0')
		return (ft_free_2d_char_arr(sep_line), EXIT_FAILURE);
	if (is_valid_data(sep_line, elem_check) == false)
	{
		ft_free_2d_char_arr(sep_line);
		return (ft_perror(MAP_ERR), EXIT_FAILURE);
	}
	
}

/* -- Notes: ---------------------------------------------------------------- *\
\* -------------------------------------------------------------------------- */

int	process_file_data(char *filename, t_gen_data *gen_data)
{
	int		map_fd;
	char	*line;
	int8_t	elem_check[8];		// Element is checked

	map_fd = open(filename, O_RDONLY);
	if (map_fd < 0)
		return (ft_perror(FD_ERR), EXIT_FAILURE)
	line = get_next_line(map_fd, 1);
	if (line == NULL)
		return (ft_perror(EMPTY_FL_ERR), EXIT_FAILURE)
	ft_bzero(&elem_check, sizeof(int8_t) * 8);
	while (line != NULL)
	{
		if (line[0] != '\n')
			check_and_init_data(line, gen_data, &elem_check);
		free(line);
		line = get_next_line(map_fd, 1);
	}
	return (EXIT_SUCCESS)
}

