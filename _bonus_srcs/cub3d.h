/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:53:32 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/18 18:14:15 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ------------------------------- LIBRARIES -------------------------------- */
// Functions & Functionalities //
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

// Macros & Typedefs //
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>

// Custom
# include "../includes/get_next_line/get_next_line.h"
# include "m4cr0s.h"
# include <mlx.h>

/* --------------------------------- ENUMS ---------------------------------- */
typedef enum s_dirctn
{
	NO,
	SO,
	WE,
	EA
}	t_dirctn;

/* -------------------------------- TYPEDEFS -------------------------------- */
typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;

/* -------------------------------- STRUCTS --------------------------------- */
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
	int		m_offset;
}	t_img;

typedef struct s_input
{
	t_img		textures[4];
	int			ceil_clr;
	int			floor_clr;
	char		**map_arr;
}	t_input;

typedef struct s_fcoords
{
	double	y;
	double	x;
}	t_fcoords;

typedef struct s_icoords
{
	int	y;
	int	x;
}	t_icoords;

typedef struct s_player
{
	t_fcoords	pos;
	double		rot;
	int			mouse_prev_x;
	char		mouse_click;
	char		turn_dir;
	char		walk_dir;
	char		walk_horizon;
}	t_player;

typedef struct s_intrsctn
{
	double	x_point;
	double	y_point;
	char	is_intersected;
}	t_intrsctn;

typedef struct s_cast_params
{
	t_fcoords	intrcpt;
	t_fcoords	step;
	t_intrsctn	*wall_hit;
}	t_cast_params;

typedef struct s_ray
{
	int			id;
	double		ray_angle;
	t_fcoords	wall_hit;
	double		distance;
	char		grid_direction;
	char		is_facing_down;
	char		is_facing_up;
	char		is_facing_right;
	char		is_facing_left;
}	t_ray;

typedef struct s_wall
{
	double		ds_proj_plane;
	double		wall_height;
	t_icoords	p0;
	t_icoords	p1;
}	t_wall;

typedef struct s_display
{
	void		*mlx;
	void		*win;
	t_img		img;
}	t_display;

typedef struct s_cub
{
	t_display	display;
	t_player	player;
	t_input		input;
}	t_cub;

/* ------------------------------- PROTOTYPES ------------------------------- */
/* DISPLAY */
void	img_pixel_put(t_img *img, t_icoords pxl, int color);

void	update_player_position(t_cub *cub);

void	draw_background(t_cub *cub);

void	draw_limited_line(t_cub *cub, t_fcoords p0, t_fcoords p1, int color);
void	draw_minimap_player(t_cub *cub, int scale);
void	draw_minimap(t_cub *cub);

void	init_display_params(t_cub *cub);

/* PARSING */
void	map_is_closed(char **map_arr);
void	only_one_player(char **map_arr, t_player *player);

void	check_init_color(char **line_split, t_input *gen_data);
void	check_init_texture(char **line_split, t_input *gen_data, void *mlx);

void	check_last_lines(char *line);

void	process_file_data(char *filename, t_cub *cub);

int		is_map_objs(char *line, int *is_mp_obj);
void	process_map_arr(t_input *data, char *line);
void	place_virtual_walls(char **map_arr);
void	trim_colors(char **colors);

/* -------------------------- EVENTS HANDLING ------------------------------- */
/* - - handle_keypress.c - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int		draw_and_output_image(t_cub *cub);
void	handle_keys(t_cub *cub);

/* - - cub3d.c - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int		xclose(void *v_cub);

/* - - handle_mouse_events.c - - - - - - - - - - - - - - - - - - - - - - - - -*/
int		mouse_hover(int x, int y, void *v_cub);
int		mouse_click(int keycode, int x, int y, void *v_cub);
int		mouse_release(int keycode, int x, int y, void *v_cub);

/* - - handle_misc_events.c - - - - - - - - - - - - - - - - - - - - - - - - - */
int		xclose(void *v_cub);

/* --------------------- RAY-CASTING CALCULATIONS --------------------------- */
/* - - misc_calculs.c - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
double	deg2rad(int deg);
int		rad2deg(double rad);
double	normalize_angle(double rotation);
int		check_wall_colision(t_player player, t_fcoords pos, char **map_arr);
double	dstnce_btwn_points(t_fcoords p, t_intrsctn intr);

/* - - casting_rays.c - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void	casting_rays(t_cub *cub);

/* - - cast.c - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void	cast(t_cub *cub, t_ray *ray);

/* - - cast_util.c - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int		wall_colision(t_fcoords pos, char **map_arr);
void	calcul_distance(t_player p, t_ray *ray, t_intrsctn horiz, \
	t_intrsctn vert);

/* -------------------- WALL CALCULATIONS AND RENDERIGN --------------------- */
void	render_walls(t_cub *cub, t_ray ray);

double	get_darkness_percent(double value, double max_value);
int		shade_color(int color, double percent);

#endif
