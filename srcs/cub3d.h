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
# include <mlx.h>

/* -------------------------------- MACROS ---------------------------------- */
# define WIN_HEIGHT		1080
# define WIN_WIDTH		1920
# define MAP_OBJS		"10NEWS "
# define MAP_DIRECTNS	"NO SO WE EA"

/* -------------------------------- ERRORS ---------------------------------- */
# define EMPTY_FL_ERR		"Empty file"
# define EXT_ERR			"Invalid file extension"
# define FD_ERR				"File not found"
# define MAP_ERR			"Invalid map: "
# define GEN_ERR			"Internal error: "
# define MLX_ERR			"Minilibx error"
# define WIN_ERR			"Window error"

/* -------------------------------- EVENTS ---------------------------------- */
// ---------- Event masks --------/
# define NO_EVENT_MASK		0L
# define KEY_PRESS_MASK		(1L<<0)
# define KEY_RELEASE_MASK	(1L<<1)

// ---------- Event type --------/
# define KEY_PRESS			2
# define DESTROY_NOTIFY		17
# define MOUSE_MOVEMENT		6

// ---------- Event keys (directions) --------/
# define KEY_UP			126
# define KEY_DOWN		125
# define KEY_RIGHT		124
# define KEY_LEFT		123
# define KEY_W			13
# define KEY_S			1
# define KEY_A			0
# define KEY_D			2

// ---------- Event keys (others) --------/
# define KEY_ESCAPE		53
# define KEY_C			8
# define KEY_R			15
# define KEY_P			35
# define KEY_X			7
# define KEY_Y			16
# define KEY_Z			6
# define KEY_PAD_SUB	78
# define KEY_PAD_ADD	69
# define KEY_PAGE_UP	116
# define KEY_PAGE_DOWN	121
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
typedef struct s_input
{
	int		texture_fds[4];

	int		ceil_clr;
	int		floor_clr;
	char	**map_arr;
}	t_input;

typedef struct s_coords
{
	int		y;
	int		x;
}	t_coords;

typedef struct s_brsnhm
{
	t_coords	dlta;
	t_coords	pxl;
	t_coords	s;
	int			err;
	int			e2;
}	t_brsnhm;

typedef struct s_player
{
	t_coords	position;		// Position
	int			rot;		// Rotation
}	t_player;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_img;

typedef struct s_display
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_display;

typedef struct s_cub
{
	t_input		input;
	t_display	display;
	t_player	player;
}	t_cub;

/* ------------------------------- PROTOTYPES ------------------------------- */
/* -  - check_map.c -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  / /
These functions are only used in the parsing (file_parcer.c) part of the project
/ / -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -*/
void	map_is_closed(char **map_arr);
void	only_one_player(char **map_arr);

/* -  - data_init.c -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  / /
These functions are only used in the parsing (file_parcer.c) part of the project
/ /-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - */
void	check_init_color(char **line_split, t_input *gen_data);
void	check_init_direction_texture(char **line_split, t_input *gen_data);

/* - - file_parser.c- - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void	process_file_data(char *filename, t_input *gen_data);

/* - - draw_line.c - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void	draw_line(t_img *img, t_coords p0, t_coords p1, int clr);

/* - - draw_minimap.c - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void	draw_minimap(t_img *img, char **map_arr, int size, t_coords start);

/* - - draw_background.c- - - - - - - - - - - - - - - - - - - - - - - - - - - */
void	draw_background(t_img *img, t_input *input);

/* - - window_manag.c - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void	reset_window(void *mlx, void *win, t_img *img);
void	init_display_params(t_cub *cub);
/* -------------------------- EVENTS HANDLING ------------------------------- */

/* - - handle_keypress.c - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void    player_movement(int keycode, t_cub *cub);
void	esc_close(int keycode, t_cub *cub);
int		key_press(int keycode, void *_cub);

/* - - cub3d.c - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int		xclose(void *v_cub);

/* - - handle_mouse_events.c - - - - - - - - - - - - - - - - - - - - - - - - -*/
int		mouse_move(int x, int y, void *_cub);

/* - - handle_misc_events.c - - - - - - - - - - - - - - - - - - - - - - - - -*/
int	xclose(void *v_cub);

#endif
