# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoezard <acoezard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/24 21:19:06 by acoezard          #+#    #+#              #
#    Updated: 2021/10/25 10:58:46 by acoezard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
CLIBFT	= -I libft/includes -L libft -lft

server:
	${CC} ${CFLAGS} ${CLIBFT} -o server ft_server.c

client:
	${CC} ${CFLAGS} ${CLIBFT} -o client ft_client.c

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
