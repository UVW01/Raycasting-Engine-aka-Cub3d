# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 10:53:27 by mnaimi            #+#    #+#              #
#    Updated: 2022/08/09 13:30:27 by mnaimi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #

CC			:= gcc
CC_FLAGS	:= -Wall -Wextra -Werror -Ofast -march=native \
	-fno-signed-zeros -fno-trapping-math

CC_OPTS		:= -I /usr/local/include \
	-framework OpenGL -framework AppKit \
	-lglfw -L $(brew --prefix glfw)/lib \
	-lmlx42 -L includes/MLX42 \
	-lft -L includes/libft \
	includes/get_next_line/get_next_line.c

# ---------------------------------------------------------------------------- #

SRCS		:= $(shell find srcs -type f -name "*.c" | grep -v "srcs/cub3d.c")

OBJS_DIR	:= .objs/
OBJS_LST	:= ${patsubst %.c, %.o, ${SRCS_LST}}
OBJS_FLS	:= ${addprefix ${OBJS_DIR}, ${OBJS_LST}}
OBJS		:= ${notdir ${OBJS_FLS}}

NAME		:= cub3d
MAIN		:= srcs/cub3d.c
HEADER		:= srcs/cub3d.h

# ---------------------------------------------------------------------------- #

.PHONY: all clean fclean re bonus

all: ${NAME}

${NAME}: ${HEADER}
	@${CC} ${CC_FLAGS} ${CC_OPTS} ${MAIN} ${SRCS} -o ${NAME}
	@echo "${NAME}: Compiled successfully"

clean:
	@make -C includes/libft clean

fclean: clean
	@rm -f ${NAME}
	@make -C includes/libft fclean

re: fclean all

#bonus: 
