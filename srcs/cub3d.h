/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:53:32 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/16 10:40:24 by mnaimi           ###   ########.fr       */
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

/* --------------------------------- ENUMS ---------------------------------- */

typedef enum s_dirctn
{
	NO,
	SO,
	WE,
	EA
}	t_dirctn;

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

typedef struct s_img
{
	void	*img_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*addr;
}	t_img;

typedef struct s_display
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_input	input;
}	t_display;

/* -------------------------------- TYPEDEFS -------------------------------- */
typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;

/* ------------------------------- PROTOTYPES ------------------------------- */
/* - - check_map.c - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / /
These functions are only used in the parsing (file_parcer.c) part of the project
/ / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void	map_is_closed(char **map_arr);
void	only_one_player(char **map_arr);

/* - - data_init.c - - - - - - - - - - - - - - - - - - - - - - - - - - - - - / /
These functions are only used in the parsing (file_parcer.c) part of the project
/ / - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void	check_init_color(char **line_split, t_input *gen_data);
void	check_init_direction_texture(char **line_split, t_input *gen_data);

/* - - file_parser.c - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void	process_file_data(char *filename, t_input *gen_data);

#endif
