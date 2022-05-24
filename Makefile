# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccartet <ccartet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/15 10:52:54 by ccartet           #+#    #+#              #
#    Updated: 2022/02/09 11:43:16 by ccartet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
LIBFT = libft/libft.a
LIBMLX = mlx/libmlx.a

SRCS = fdf.c get_map.c init.c get_map_utils.c key_hook.c drawing_map.c projection.c
OBJS = ${addprefix ${OBJD}, ${SRCS:.c=.o}}

SRCD = srcs/
OBJD = obj/

OBJ_DIR = $(sort $(dir $(OBJS)))

CFLAGS = -Wall -Wextra -Werror -I includes -I mlx -I libft
SL = -framework OpenGL -framework AppKit

all: libs $(NAME)

${OBJS}:	| ${OBJ_DIR}

${OBJ_DIR}:
	mkdir -p $@

${OBJD}%.o: ${SRCD}%.c includes/fdf.h mlx/mlx.h libft/libft.h
	gcc ${CFLAGS} -c -o $@ $<

${NAME}:	${OBJS} ${LIBFT} ${LIBMLX}
	gcc ${CFLAGS} ${SL} ${OBJS} ${LIBFT} ${LIBMLX} -o ${NAME}

libs:
	$(MAKE) -C libft/
	$(MAKE) -C mlx/
	
clean:
	rm -rf ${OBJD}
	$(MAKE) clean -C libft/
	$(MAKE) clean -C mlx/

fclean:	
	rm -rf ${NAME} ${OBJD}
	$(MAKE) fclean -C libft/
	$(MAKE) clean -C mlx/

re:	fclean all

.PHONY:	all libs clean fclean re
