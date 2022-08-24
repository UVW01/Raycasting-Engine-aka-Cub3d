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

void	draw_player(t_coords point, t_img *img, int size)
{
	t_coords	p;

	p.x = (point.x - (size / 2));
	p.y = (point.y - (size / 2));
	while (p.y <= point.y + (size / 2))
	{
		draw_line(img, p, (t_coords){.x = p.x + size, .y = p.y}, 0xFF0000);
		p.y++;
	}
}

/* -------------------------------------------------------------------------- */

static void	draw_square(t_coords point, t_img *img, int color)
{
	t_coords	p;

	p.x = (point.x * 64) + 1; // should remove the + 1
	p.y = (point.y * 64) + 1; // also here
	while (p.y <= (point.y * 64) + 63) // should be 64
	{
		draw_line(img, p, (t_coords){.x = p.x + 63, .y = p.y}, color); // 64 !62
		p.y++;
	}
}

/* -------------------------------------------------------------------------- */

void	draw_minimap(t_cub *cub)
{
	t_coords	loop;
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
			draw_square((t_coords){.x = loop.x, .y = loop.y},\
				&cub->display.img, color);
		}
	}
}

/* -------------------------------------------------------------------------- */

static void	draw_fov(t_player *player, t_img *img)
{
	t_coords	new_pos;

	new_pos.x = player->pos.x + (cos(player->rot) * 160);
	new_pos.y = player->pos.y + (sin(player->rot) * 160);
	draw_line(img, player->pos, new_pos, 0x0000FF);
}

/* -------------------------------------------------------------------------- */

void	move_horizontally(t_player *player, t_img *img, int walk_dir, \
	char **map_arr)
{
	double		new_rot;
	t_coords	tmp;
	int			steps;

	steps = walk_dir * 4;
	new_rot = player->rot + deg2rad(90);
	tmp.x = player->pos.x + (cos(new_rot) * steps);
	tmp.y = player->pos.y + (sin(new_rot) * steps);
	if (!check_wall_colision(tmp, map_arr))
		player->pos = tmp;
	draw_fov(player, img);
}

/* -------------------------------------------------------------------------- */

int multiple_of_n(int number, int n)
{
	return (ceil(number / n) * n);
}

/* -------------------------------------------------------------------------- */

// static double	normalize_angle(double rotation)
// {
// 	rotation = deg2rad(rad2deg(rotation) % 360);
// 	if (rotation < 0)
// 		rotation += M_PI * 2;
// 	return (rotation);
// }

/* -------------------------------------------------------------------------- */

int	check_wall_colision(t_coords pos, char **map_arr)
{
	t_coords	temp;

	temp.x = pos.x / 64;
	temp.y = pos.y / 64;
	if (map_arr[temp.y][temp.x] == '1')
		return (1);
	return (0);
}
//!	should check if the resulting number exists as a dimension in map_arr

/* -------------------------------------------------------------------------- */

void	update_player_position(t_player *player, t_img *img, char **map_arr)
{
	int			steps;
	t_coords	tmp;

	steps = player->walk_dir * 4;
	player->rot += deg2rad(player->turn_dir * 10);
	tmp.x = player->pos.x + (cos(player->rot) * steps);
	tmp.y = player->pos.y + (sin(player->rot) * steps);
	if (!check_wall_colision(tmp, map_arr))
		player->pos = tmp;
	draw_fov(player, img);
}

/* -------------------------------------------------------------------------- */


