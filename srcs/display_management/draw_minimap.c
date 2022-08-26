/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:12:18 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/14 21:21:46 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* -------------------------------------------------------------------------- */

void	draw_player(t_icoords point, t_img *img, int size)
{
	t_icoords	p;

	p.x = (point.x - (size / 2));
	p.y = (point.y - (size / 2));
	while (p.y <= point.y + (size / 2))
	{
		draw_line(img, p, (t_icoords){.x = p.x + size, .y = p.y}, 0xFF0000);
		p.y++;
	}
}

/* -------------------------------------------------------------------------- */

static void	draw_square(t_icoords point, t_img *img, int color)
{
	t_icoords	p;

	p.x = (point.x * CUB_SIZE) + 1; // should remove the + 1
	p.y = (point.y * CUB_SIZE) + 1; // also here
	while (p.y <= (point.y * CUB_SIZE) + (CUB_SIZE - 1)) // should be 64
	{
		draw_line(img, p, (t_icoords){.x = p.x + (CUB_SIZE - 1), .y = p.y}, \
			color); // 64 !62
		p.y++;
	}
}

/* -------------------------------------------------------------------------- */

void	draw_minimap(t_cub *cub)
{
	t_icoords	loop;
	int			color;

	loop.y = -1;
	while (cub->input.map_arr[++loop.y])
	{
		loop.x = -1;
		while (cub->input.map_arr[loop.y][++loop.x])
		{
			color = 0xF0F0F0;
			if (cub->input.map_arr[loop.y][loop.x] == ' ')
				continue ;
			else if (cub->input.map_arr[loop.y][loop.x] == '1')
				color = 0x3F3F3F;
			draw_square((t_icoords){.x = loop.x, .y = loop.y},\
				&cub->display.img, color);
		}
	}
}

/* -------------------------------------------------------------------------- */

static void	draw_fov(t_player *player, t_img *img)
{
	t_icoords	new_pos;

	new_pos.x = player->pos.x + (cos(player->rot) * 160);
	new_pos.y = player->pos.y + (sin(player->rot) * 160);
	draw_line(img, player->pos, new_pos, 0x0000FF);

}

/* -------------------------------------------------------------------------- */

void	move_horizontally(t_player *player, t_img *img, int walk_dir)
{
	float	new_rot;
	int		steps;

	steps = walk_dir * 8;
	new_rot = player->rot + deg2rad(90);
	player->pos.x += cos(new_rot) * steps;
	player->pos.y += sin(new_rot) * steps;
	draw_fov(player, img);
}

/* -------------------------------------------------------------------------- */

int multiple_of_n(int number, int n)
{
	return (ceil(number / n) * n);
}

/* -------------------------------------------------------------------------- */

// int	check_wall_colision(t_icoords pos, char **map_arr)
// {
// 	t_icoords	temp;

// 	temp.x = pos.x / CUB_SIZE;
// 	temp.y = pos.y / CUB_SIZE;
// 	if (map_arr[temp.y][temp.x] == '1')
// 		return (1);
// 	return (0);
// }
// //!	should check if the resulting number exists as a dimension in map_arr

/* -------------------------------------------------------------------------- */

void	update_player_position(t_player *player, t_img *img, char **map_arr)
{
	int			steps;
	t_icoords	tmp;

	player->rot += (player->turn_dir * 0.0349066);
	player->rot = normalize_angle(player->rot);
	steps = player->walk_dir * 2.0;

	tmp.x = floor(player->pos.x + (cos(player->rot) * steps));
	tmp.y = floor(player->pos.y + (sin(player->rot) * steps));

	if (!check_wall_colision(tmp, map_arr))
		player->pos = tmp;
	draw_fov(player, img);
}

/* -------------------------------------------------------------------------- */


