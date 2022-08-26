/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m4cr0s.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 06:53:32 by mnaimi            #+#    #+#             */
/*   Updated: 2022/08/18 18:14:15 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M4CR0S_H
# define M4CR0S_H

/* -------------------------------- WINDOW ---------------------------------- */
# define WIN_HEIGHT		1080
# define WIN_WIDTH		2400
# define CUB_SIZE		64
# define FOV_ANGLE		60 * (M_PI /180)
# define RAYS_LENGTH	WIN_WIDTH

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
// ---------- Event masks -------- //
# define NO_EVENT_MASK		0L
# define KEY_PRESS_MASK		0b00000001
# define KEY_RELEASE_MASK	0b00000010

// ---------- Event type -------- //
typedef enum s_event_types {
	KEY_PRESS = 2,
	KEY_RELEASE = 3,
	MOUSE_MOVEMENT = 6,
	DESTROY_NOTIFY = 17,
}	t_event_types;

// ---------- Event keys (directions) ------- //
typedef enum s_event_direction_keys {
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_W = 13,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
	KEY_UP = 126,
}	t_event_direction_keys;

// ---------- Event keys (others) -------- //
typedef enum s_event_other_keys {
	KEY_Z = 6,
	KEY_X = 7,
	KEY_C = 8,
	KEY_R = 15,
	KEY_Y = 16,
	KEY_P = 35,
	KEY_ESCAPE = 53,
	KEY_PAD_ADD	= 69,
	KEY_PAD_SUB	= 78,
	KEY_PAGE_UP	= 116,
	KEY_PAGE_DOWN = 121,
}	t_event_other_keys;

#endif
