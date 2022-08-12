# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 10:53:27 by mnaimi            #+#    #+#              #
#    Updated: 2022/08/12 13:53:07 by mnaimi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #

CC			:= gcc
CC_FLAGS	:= -Wall -Wextra -Werror --std=c99 --pedantic 
#-fsanitize=address -static-libsan
#-Ofast -march=native -fno-signed-zeros -fno-trapping-math

CC_OPTS		:= -I /usr/local/include \
	-framework OpenGL -framework AppKit \
	-lmlx42 -L includes/MLX42 \
	-lft -L includes/libft \
	includes/get_next_line/get_next_line.c
# -lglfw -L $(brew --prefix glfw)/lib

# ---------------------------------------------------------------------------- #

SRCS_DIR	:= srcs/
SRCS_LST	:= map_parsing/file_reader.c
SRCS		:= ${addprefix ${SRCS_DIR}, ${SRCS_LST}}

NAME		:= cub3d
MAIN		:= srcs/cub3d.c
HEADER		:= srcs/cub3d.h

# ---------------------------------------------------------------------------- #

.PHONY: all clean fclean re

all: ${NAME}

${NAME}: ${HEADER}
	@make -C includes/libft
	@${CC} ${CC_FLAGS} ${CC_OPTS} ${MAIN} ${SRCS} -o ${NAME}
	@echo "${NAME}: Compiled successfully"

clean:
	@make -C includes/libft clean

fclean: clean
	@rm -f ${NAME}
	@make -C includes/libft fclean

re: fclean all
