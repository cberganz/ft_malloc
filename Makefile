# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 14:42:18 by cberganz          #+#    #+#              #
#    Updated: 2023/02/10 23:43:37 by charles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= malloc

INCLUDE			= includes/

HEADER			= ${INCLUDE}malloc.h

CC				= cc

CFLAGS			= -Wall -Wextra -Werror -g

SRC_NAME		= malloc.c \
				  main.c\

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
