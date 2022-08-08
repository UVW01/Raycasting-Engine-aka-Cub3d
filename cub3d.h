/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:53:32 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/08 15:11:51 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ------------------------------- LIBRARIES -------------------------------- */
// Functions & Functionalities //
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>

// Macros & Typedefs //
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>

// Custom
# include "includes/get_next_line/get_next_line.h"

/* -------------------------------- ERRORS ---------------------------------- */
# define EXT_ERR	"Invalid file extension"
# define FD_ERR		"File not found"
# define MAP_ERR	"Invalid map"
# define FL_ERR		"Empty file"

/* -------------------------------- STRUCTS --------------------------------- */
typedef struct s_gen_data
{
	int		texture_fds[4];
	int32_t	ceil_clr;
	int32_t	floor_clr;
	int8_t	**map_arr;
}	t_gen_data;

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
