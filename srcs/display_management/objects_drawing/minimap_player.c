/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:12:18 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/14 21:21:46 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

static void	draw_fov(t_fcoords start_pos, t_fcoords end_pos, t_cub *cub)
{
	t_fcoords	player_pos;
	t_icoords	offset;
	int			square_size;
	int			minimap_half_size;

	square_size = (WIN_HEIGHT / 4) / 11;
	minimap_half_size = (WIN_HEIGHT / 4) / 2;
	player_pos = cub->player.pos;
	offset.x = ((player_pos.x * square_size) / CUB_SIZE);
	offset.y = ((player_pos.y * square_size) / CUB_SIZE);
	start_pos.x = (((start_pos.x * square_size) / CUB_SIZE) - offset.x);
	start_pos.y = (((start_pos.y * square_size) / CUB_SIZE) - offset.y);
	end_pos.x = (((end_pos.x * square_size) / CUB_SIZE) - offset.x);
	end_pos.y = (((end_pos.y * square_size) / CUB_SIZE) - offset.y);
	start_pos.x += minimap_half_size;
	start_pos.y += minimap_half_size;
	end_pos.x += minimap_half_size;
	end_pos.y += minimap_half_size;
	draw_limited_line(cub, start_pos, end_pos, 0x20FFAF00);
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

static void	reinit_ray_infos(t_ray *ray)
{
	ray->is_facing_down = false;
	ray->is_facing_up = false;
	ray->is_facing_right = false;
	ray->is_facing_left = false;
	if (ray->ray_angle > M_PI && ray->ray_angle < (2 * M_PI))
		ray->is_facing_up = true;
	else
		ray->is_facing_down = true;
	if (ray->ray_angle < (0.5 * M_PI) || ray->ray_angle > (1.5 * M_PI))
		ray->is_facing_right = true;
	else
		ray->is_facing_left = true;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

static void	recasting_rays(t_cub *cub)
{
	t_ray	ray;
	int		i;

	ft_bzero(&ray, sizeof(t_ray));
	ray.ray_angle = (cub->player.rot - (FOV_ANGLE / 2));
	i = -1;
	while (++i < RAYS_LENGTH)
	{
		ray.ray_angle = normalize_angle(ray.ray_angle);
		reinit_ray_infos(&ray);
		cast(cub, &ray);
		ray.id = i;
		draw_fov(cub->player.pos, ray.wall_hit, cub);
		ray.ray_angle += (FOV_ANGLE / RAYS_LENGTH);
	}
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

void	draw_minimap_player(t_cub *cub, int scale)
{
	t_icoords	new_pos;
	t_icoords	loop;
	int			size;

	recasting_rays(cub);
	size = WIN_HEIGHT / scale;
	new_pos = (t_icoords){.x = (size / 2), .y = (size / 2)};
	loop.y = -2;
	while (++loop.y < 3)
	{
		loop.x = -2;
		while (++loop.x < 3)
		{
			img_pixel_put(&cub->display.img, (t_icoords){.x = new_pos.x + \
				loop.x, .y = new_pos.y + loop.y}, 0xFF0000);
		}
	}
}
