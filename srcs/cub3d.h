/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:53:32 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/13 17:42:29 by mnaimi           ###   ########.fr       */
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
# define WIN_WIDTH		1920
# define WIN_HEIGHT		1080
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
	NO,		// North
	SO,		// South
	WE,		// West
	EA		// East
}	t_dirctn;

/* -------------------------------- STRUCTS --------------------------------- */
typedef struct s_gen_data
{
	int		texture_fds[4];
	int		ceil_clr;
	int		floor_clr;
	char	**map_arr;
}	t_gen_data;						// General Data

typedef struct s_coords
{
	int		y;
	int		x;
}	t_coords;	

/* -------------------------------- TYPEDEFS -------------------------------- */
typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;

/* ------------------------------- PROTOTYPES ------------------------------- */
//* check_map.c
void		map_is_closed(char **map_arr);
void		only_one_player(char **map_arr);

//* data_init.c
//*	These functions are only used in the parsing part (file_parcer.c) 
//*	of the project
void	check_init_color(char **line_split, t_gen_data *gen_data);
void	check_init_direction_texture(char **line_split, t_gen_data *gen_data);

//	file_parser.c
int		process_file_data(char *filename, t_gen_data *gen_data);

#endif
