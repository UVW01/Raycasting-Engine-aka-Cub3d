/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:53:32 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/16 10:58:50 by mnaimi           ###   ########.fr       */
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

/* ------------------------------- mlx stuff ------------------------------- */
 
// window stuff
typedef struct	s_win {
	void	*mlx;
	void	*win;
}				t_win;

// drawing stuff
typedef struct	s_data {
	void	*img;
    int     img_height;
    int     img_width;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_args;

/* ----------------------------- dda algo stuff --------------------------- */
typedef struct s_dda
{
    int x0;
    int x1;
    int y0;
    int y1;
    int color;
}   t_dda;

typedef struct s_player
{
	int x;
	int	y;
	int updown;
	int	rotation;
}	t_player;

/* ------------------- struct that conteans all data ------------------------ */

typedef struct s_cub
{
	t_input		gen_data;
	t_win		win;
	t_img_args	map_img;
	t_img_args	player_img;
	t_player	player;
}	t_cub;

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

/*--------------------------------DRAWING LOGIC--------------------------------*/

void	my_mlx_pixel_put(t_img_args *data, int x, int y, int color);
void	DDA_util(t_dda dda, int *steps, float *Xinc, float *Yinc);
void	DDA(t_dda dda, t_img_args *img);
void	draw_box(int x, int y, int color, t_img_args *img);
void    draw_player(int x, int y, int color, t_cub *cub);

/*--------------------------------2D_RENDERING--------------------------------*/
void    render_2d(t_cub *cub);
void	render_player(t_cub *cub);
void	towD_rendering(t_cub *cub);

/*--------------------------------RENDER--------------------------------*/
void	render(t_cub *cub);

#endif
