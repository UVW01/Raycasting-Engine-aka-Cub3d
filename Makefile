# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 10:53:27 by mnaimi            #+#    #+#              #
#    Updated: 2022/08/13 17:44:26 by mnaimi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #

CC			:= gcc
CC_FLAGS	:= -Wall -Wextra -Werror \
	-fsanitize=address -static-libsan
# -Ofast -march=native -fno-signed-zeros -fno-trapping-math
# --std=c99 --pedantic 

CC_OPTS		:= -I /usr/local/include -L/usr/local/lib/ -lmlx \
	-framework OpenGL -framework AppKit -lft -L includes/libft \
	includes/get_next_line/get_next_line.c

# ---------------------------------------------------------------------------- #

GEN_LST	:= file_parcer.c data_init.c check_map.c

MINI_MAP :=	bresenham_line_algo.c \
			coordinates_calculs.c \
			objects_drawing.c \
			window_management.c

EVENTS	:= 	handle_keypress.c handle_mouse_events.c handle_misc_events.c
CASTING_RAYS := casting_rays.c cast.c misc_functs.c

SRCS		:= ${addprefix srcs/map_parsing/, ${GEN_LST}} \
				${addprefix srcs/display_management/, ${MINI_MAP}} \
				${addprefix srcs/event_handling/, ${EVENTS}} \
				${addprefix srcs/raycast_calculs/, ${CASTING_RAYS}}

NAME		:= cub3d
MAIN		:= srcs/cub3d.c
HEADER		:= srcs/cub3d.h

# ---------------------------------------------------------------------------- #

.PHONY: all clean fclean re

all: ${NAME}

${NAME}: ${HEADER} ${MAIN} ${SRCS}
	@echo "Making dependencies, please wait ..."
	@make -C includes/libft >> /dev/null
	@echo "Making ./cub3d executable, please wait ..."
	@${CC} ${CC_FLAGS} ${CC_OPTS} ${MAIN} ${SRCS} -o ${NAME}
	@echo "${NAME}: Compiled successfully"

clean:
	@make clean -C includes/libft >> /dev/null

fclean: clean
	@rm -f ${NAME}
	@make fclean -C includes/libft >> /dev/null

re: fclean all
