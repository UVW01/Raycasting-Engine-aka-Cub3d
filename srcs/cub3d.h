/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:53:32 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/09 15:11:38 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ------------------------------- LIBRARIES -------------------------------- */
// Functions & Functionalities //
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

// Macros & Typedefs //
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>

// Custom
# include "../includes/get_next_line/get_next_line.h"
# include "../includes/MLX42/include/MLX42/MLX42.h"

/* -------------------------------- MACROS ---------------------------------- */
# define WIN_WIDTH		800
# define WIN_HEIGHT		600
# define MAP_ELEMENTS	"NO SO WE EA F C"
# define MAP_OBJS		"NO SO WE EA F C"

/* -------------------------------- ERRORS ---------------------------------- */
# define EMPTY_FL_ERR		"Empty file"
# define EXT_ERR			"Invalid file extension"
# define FD_ERR				"File not found"
# define MAP_ERR			"Invalid map"
# define GEN_ERR			"Internal error"

/* -------------------------------- STRUCTS --------------------------------- */
typedef struct s_gen_data
{
	int		texture_fds[4];
	int32_t	ceil_clr;
	int32_t	floor_clr;
	int8_t	**map_arr;
}	t_gen_data;			// general_data

/* --------------------------------- ENUMS ---------------------------------- */

typedef enum s_directions
{
	NO,		// North
	SO,		// South
	WE,		// West
	EA		// East
}	t_directions;

typedef enum s_map_objs
{
	I_SPC,		// Inside_SPaCe			(playable space)
	O_SPC,		// Outside_SPaCe		(non playable space)
	WALL,		// (Self-explanatory)
	P_POS,		// Player_POSition		(player's spawn point)
}	t_map_objs;

/* -------------------------------- TYPEDEFS -------------------------------- */
typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;

/* ------------------------------- PROTOTYPES ------------------------------- */

#endif
