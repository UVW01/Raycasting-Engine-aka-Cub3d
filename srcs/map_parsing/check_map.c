/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 20:28:19 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/13 17:47:40 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -- Notes: ---------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

static void	check_horizontally(char **map_arr, t_coords *coords)
{
	char	*elems;
	int		len;
	int		x;

	elems = map_arr[coords->y];
	len = ft_strlen(elems);
	x = coords->x;
	while (--x >= 0)
	{
		if (elems[x] == '1')
			break ;
		else if ((x == 0 && elems[x] != '1') || elems[x] == ' ')
			ft_perror(MAP_ERR"Unclosed/Invalid map elements", 1);
	}
	x = coords->x;
	while (elems[++x])
	{
		if (elems[x] == '1')
			break ;
		else if ((x == len - 1 && elems[x] != '1') || elems[x] == ' ')
			ft_perror(MAP_ERR"Unclosed/Invalid map elements", 1);
	}
}

static void	check_vertically(char **map_arr, t_coords *coords)
{
	int		y;

	y = coords->y;
	while (--y >= 0)
	{
		if (map_arr[y][coords->x] == '1')
			break ;
		else if ((y == 0 && map_arr[y][coords->x] != '1') || \
			map_arr[y][coords->x] == ' ')
			ft_perror(MAP_ERR"Unclosed/Invalid map elements", 1);
	}
	y = coords->y;
	while (map_arr[++y])
	{
		if (map_arr[y][coords->x] == '1')
			break ;
		else if ((map_arr[y + 1] == NULL && map_arr[y][coords->x] != '1') || \
			map_arr[y][coords->x] == ' ')
			ft_perror(MAP_ERR"Unclosed/Invalid map elements", 1);
	}
}

void	map_is_closed(char **map_arr)
{
	t_coords	coords;

	coords.y = -1;
	while (map_arr[++coords.y])
	{
		coords.x = -1;
		while (map_arr[coords.y][++coords.x])
		{
			if ((map_arr[coords.y][coords.x] == '0' ||
				map_arr[coords.y][coords.x] == 'N' ||
				map_arr[coords.y][coords.x] == 'E' ||
				map_arr[coords.y][coords.x] == 'W' ||
				map_arr[coords.y][coords.x] == 'S'))
			{
				check_vertically(map_arr, &coords);
				check_horizontally(map_arr, &coords);
			}
		}
	}
}


/* -- Notes: ---------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

void	only_one_player(char **map_arr)
{
	int			count;
	t_coords	coords;

	count = 0;
	coords.y = -1;
	while (map_arr[++coords.y])
	{
		coords.x = -1;
		while (map_arr[coords.y][++coords.x])
		{
			if (map_arr[coords.y][coords.x] == 'N' ||
				map_arr[coords.y][coords.x] == 'E' ||
				map_arr[coords.y][coords.x] == 'W' ||
				map_arr[coords.y][coords.x] == 'S')
				++count;
		}
	}
	if (count != 1)
		ft_perror(MAP_ERR"More than one player spawn point", 1);
}
