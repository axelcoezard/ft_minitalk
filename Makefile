# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/24 21:19:06 by acoezard          #+#    #+#              #
#    Updated: 2021/10/25 14:21:54 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

FILES =	ft_putchar_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
		ft_atoi.c ft_isdigit.c ft_isspace.c
SRCS =	${addprefix utils/, ${FILES}}
OBJS =	${SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${OBJS} server.o client.o
	${CC} ${CFLAGS} -o server ${OBJS} server.o
	${CC} ${CFLAGS} -o client ${OBJS} client.o

clean:
	rm -rf ${OBJS} server.o client.o

fclean: clean
	rm -rf server client

re: fclean all

.PHONY: all clean fclean re
