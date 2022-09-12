/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 20:28:19 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/16 10:34:36 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -------------------------------------------------------------------------- */

int	is_map_objs(char *line, int *is_mp_obj)
{
	char	*tmp;

	tmp = ft_strtrim(line, MAP_OBJS);
	if (tmp[0] == '\0')
	{
		if (*is_mp_obj == 0)
			*is_mp_obj = 1;
		return (free(tmp), 1);
	}
	return (free(tmp), 0);
}

/* -------------------------------------------------------------------------- */

void	process_map_arr(t_input *data, char *line)
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

/* -------------------------------------------------------------------------- */

static int	is_diognal_wall(char **map_arr, t_icoords index)
{
	if (map_arr[index.y][index.x] == '1' && \
		index.x + 1 < (int)ft_strlen(map_arr[index.y + 1]) && \
		map_arr[index.y + 1][index.x + 1] == '1' && \
		map_arr[index.y + 1][index.x] == '0' && \
		map_arr[index.y][index.x + 1] == '0')
		return (1);
	else if (index.x != 0 && map_arr[index.y][index.x] == '1' && \
		index.x - 1 < (int)ft_strlen(map_arr[index.y + 1]) && \
		map_arr[index.y + 1][index.x - 1] == '1' && \
		map_arr[index.y + 1][index.x] == '0' && \
		map_arr[index.y][index.x - 1] == '0')
		return (2);
	return (0);
}

/* -------------------------------------------------------------------------- */

void	place_virtual_walls(char **map_arr)
{
	t_icoords	index;

	index.y = -1;
	while (map_arr[++index.y])
	{
		index.x = -1;
		while (map_arr[index.y][++index.x])
		{
			if (map_arr[index.y + 1] == NULL)
				break ;
			else if (is_diognal_wall(map_arr, index) == 1)
			{
				map_arr[index.y + 1][index.x] = '2';
				map_arr[index.y][index.x + 1] = '2';
			}
			else if (is_diognal_wall(map_arr, index) == 2)
			{
				map_arr[index.y + 1][index.x] = '2';
				map_arr[index.y][index.x - 1] = '2';
			}
		}
	}
}

/* -------------------------------------------------------------------------- */

void	trim_colors(char **colors)
{
	int		i;
	char	*ptr;

	i = 0;
	while (colors[i])
	{
		ptr = colors[i];
		colors[i] = ft_strtrim(colors[i], " ");
		free(ptr);
		i++;
	}
}
