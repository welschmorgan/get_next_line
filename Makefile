#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/28 09:14:15 by mwelsch           #+#    #+#              #
#    Updated: 2016/03/28 12:47:13 by mwelsch          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = gnl
SRCS = $(shell find . -maxdepth 1 -name "*.c" -type f)
OBJS = $(patsubst %.c,%.o,$(SRCS))

CFLAGS=-Wall -Werror -Wextra -g
LDFLAGS=-Llibft/ -lft

all: lib $(NAME)

$(NAME): $(OBJS) libft/libft.a
	clang -o $@ $^ $(LDFLAGS)

%.o: %.c
	clang $(CFLAGS) -c -o $@ $^ -I. -Ilibft/includes

libft/libft.a:
	make -C libft

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

lib: libft/libft.a

re: fclean $(NAME)

.PHONY: clean fclean re all lib