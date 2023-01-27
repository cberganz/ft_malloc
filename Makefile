# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 14:42:18 by cberganz          #+#    #+#              #
#    Updated: 2023/01/27 13:21:57 by charles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= test

INCLUDE			= include/

HEADER			= ${INCLUDE}malloc.h

CC				= clang

CFLAGS			= -Wall -Wextra -Werror -g

SRC_NAME		= main.c \
				  malloc.c

SRC_DIR			= srcs/
SRC				= ${addprefix ${SRC_DIR}, ${SRC_NAME}}

OBJ_DIR			= objs/
OBJ_DIRS		= ${sort ${dir ${OBJ}}}
OBJ_NAME		= ${SRC_NAME:.c=.o}
OBJ				= ${addprefix ${OBJ_DIR}, ${OBJ_NAME}}

all: ${NAME}

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) ${OBJ} -o $(NAME)

${OBJ_DIRS}:
	mkdir -p $@

${OBJ}: | ${OBJ_DIRS}

${OBJ_DIR}%.o: ${SRC_DIR}%.c ${HEADER}
	${CC} ${CFLAGS} -I${INCLUDE} -c $< -o $@

clean:
	rm -rf ${OBJ_DIR}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY : all clean fclean re
