# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccartet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 17:06:54 by ccartet           #+#    #+#              #
#    Updated: 2021/11/05 17:07:10 by ccartet          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =	ft_isalpha.c		ft_isdigit.c		ft_isalnum.c		ft_isascii.c		ft_isprint.c	\
		ft_bzero.c			ft_calloc.c			ft_memset.c			ft_memchr.c			ft_memcmp.c		\
		ft_memcpy.c			ft_memmove.c	\
		ft_atoi.c			ft_itoa.c			ft_split.c			ft_strchr.c			ft_strrchr.c	\
		ft_strdup.c			ft_striteri.c		ft_strjoin.c		ft_strlcat.c		ft_strlcpy.c	\
		ft_substr.c			ft_strmapi.c		ft_strncmp.c		ft_strnstr.c		ft_strtrim.c	\
		ft_strlen.c			ft_tolower.c		ft_toupper.c	\
		ft_putchar_fd.c		ft_putstr_fd.c		ft_putendl_fd.c		ft_putnbr_fd.c	\
		ft_lstnew.c			ft_lstadd_front.c	ft_lstadd_back.c	ft_lstsize.c		ft_lstlast.c	\
		ft_del.c			ft_lstdelone.c		ft_lstclear.c		ft_lstiter.c		ft_lstmap.c		\
		get_next_line.c		printf.c			printf_utils.c		ft_strlen_number.c	ft_find_i.c

OBJS = ${addprefix ${OBJD}, ${SRCS:.c=.o}}

OBJD = lib_obj/

OBJ_DIR = $(sort $(dir $(OBJS)))

CFLAGS = -Wall -Wextra -Werror

all:	${NAME}

${OBJS}:	| ${OBJ_DIR}

${OBJ_DIR}:
	mkdir -p $@

${OBJD}%.o: %.c libft.h
	gcc ${CFLAGS} -c -o $@ $<

${NAME}:	${OBJS}
	@ar rcs ${NAME} ${OBJS}
	@echo ${NAME} complete

clean:
	@rm -rf ${OBJD}
	@echo all object files removed
 
fclean:	clean
	@rm -rf ${NAME} ${OBJD}
	@echo library removed

re:	fclean all

.PHONY:	all bonus clean fclean re
