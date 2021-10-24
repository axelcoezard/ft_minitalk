# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/24 21:19:06 by acoezard          #+#    #+#              #
#    Updated: 2021/10/24 22:56:35 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
CLIBFT	= -Llibft/includes -lft

%.o: %.c
	${CC} ${CFLAGS} -c $< ${CLIBFT} -o $@

server: ft_server.o
	${CC} ${CFLAGS} -c ft_server.o ${CLIBFT} -o server

client: ft_client.o
	${CC} ${CFLAGS} -c ft_client.o ${CLIBFT} -o client

all: libft server client

libft:
	@make -C ./libft

clean:
	@make -C ./libft clean
	rm -rf ft_server.o ft_client.o

fclean: clean
	@make -C ./libft fclean
	rm -rf server client

re: fclean all

.PHONY: all libft server client clean fclean re
