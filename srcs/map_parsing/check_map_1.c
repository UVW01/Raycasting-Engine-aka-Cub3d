/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 20:28:19 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/16 10:34:36 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -------------------------------------------------------------------------- */

static void	check_horizontally(char **map_arr, t_icoords *pixel)
{
	char	*elems;
	int		len;
	int		x;

	elems = map_arr[pixel->y];
	len = ft_strlen(elems);
	x = pixel->x;
	while (--x >= 0)
	{
		if (elems[x] == '1')
			break ;
		else if ((x == 0 && elems[x] != '1') || elems[x] == ' ')
			ft_perror(MAP_ERR"(unclosed)1", 1);
	}
	x = pixel->x;
	while (elems[++x])
	{
		if (elems[x] == '1')
			break ;
		else if ((x == len - 1 && elems[x] != '1') || elems[x] == ' ')
			ft_perror(MAP_ERR"(unclosed)2", 1);
	}
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

static void	check_vertically(char **map_arr, t_icoords *pixel)
{
	int		y;

	y = pixel->y;
	while (--y >= 0)
	{
		if (pixel->x < (int)ft_strlen(map_arr[y]) \
			&& map_arr[y][pixel->x] == '1')
			break ;
		else if ((pixel->x >= (int)ft_strlen(map_arr[y])) \
			|| (y == 0 && map_arr[y][pixel->x] != '1') \
			|| map_arr[y][pixel->x] == ' ')
			ft_perror(MAP_ERR"(unclosed)3", 1);
	}
	y = pixel->y;
	while (map_arr[++y])
	{
		if (pixel->x < (int)ft_strlen(map_arr[y]) \
			&& map_arr[y][pixel->x] == '1')
			break ;
		else if ((pixel->x >= (int)ft_strlen(map_arr[y])) \
			|| (map_arr[y + 1] == NULL && map_arr[y][pixel->x] != '1') \
			|| map_arr[y][pixel->x] == ' ')
			ft_perror(MAP_ERR"(unclosed)4", 1);
	}
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void	map_is_closed(char **map_arr)
{
	t_icoords	pixel;

	pixel.y = -1;
	while (map_arr[++pixel.y])
	{
		pixel.x = -1;
		while (map_arr[pixel.y][++pixel.x])
		{
			if (ft_strchr("0NEWS", map_arr[pixel.y][pixel.x]))
			{
				check_vertically(map_arr, &pixel);
				check_horizontally(map_arr, &pixel);
			}
		}
	}
}

/* -------------------------------------------------------------------------- */

static int	get_proper_deg(char direction)
{
	if (direction == 'N')
		return (270);
	else if (direction == 'S')
		return (90);
	else if (direction == 'E')
		return (0);
	else if (direction == 'W')
		return (180);
	return (0);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void	only_one_player(char **map_arr, t_player *player)
{
	int			count;
	t_icoords	pixel;

	count = 0;
	pixel.y = -1;
	while (map_arr[++pixel.y])
	{
		pixel.x = -1;
		while (map_arr[pixel.y][++pixel.x])
		{
			if (!ft_strchr("NEWS", map_arr[pixel.y][pixel.x]))
				continue ;
			player->rot = deg2rad(get_proper_deg(map_arr[pixel.y][pixel.x]));
			player->pos = (t_fcoords){.x = (pixel.x * CUB_SIZE) + CUB_SIZE / 2, \
				.y = (pixel.y * CUB_SIZE) + (CUB_SIZE / 2)};
			++count;
		}
	}
	if (count != 1)
		ft_perror(MAP_ERR"(player error)", 1);
}
