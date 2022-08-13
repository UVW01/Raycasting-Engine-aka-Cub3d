# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnaimi <mnaimi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 10:53:27 by mnaimi            #+#    #+#              #
#    Updated: 2022/08/13 11:26:01 by mnaimi           ###   ########.fr        #
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
SRCS_LST	:= map_parsing/file_parcer.c map_parsing/data_init.c
SRCS		:= ${addprefix ${SRCS_DIR}, ${SRCS_LST}}

NAME		:= cub3d
MAIN		:= srcs/cub3d.c
HEADER		:= srcs/cub3d.h

# ---------------------------------------------------------------------------- #

.PHONY: all clean fclean re

all: ${NAME}

${NAME}: ${HEADER}
	@echo "Making dependencies, please wait ..."
	@make -C includes/MLX42 >> /dev/null
	@make -C includes/libft >> /dev/null
	@echo "Making ./cub3d executable, please wait ..."
	@${CC} ${CC_FLAGS} ${CC_OPTS} ${MAIN} ${SRCS} -o ${NAME}
	@echo "${NAME}: Compiled successfully"

clean:
	@make clean -C includes/libft >> /dev/null
	@make clean -C includes/MLX42 >> /dev/null
	

fclean: clean
	@rm -f ${NAME}
	@make fclean -C includes/libft >> /dev/null
	@make fclean -C includes/MLX42 >> /dev/null

re: fclean all
