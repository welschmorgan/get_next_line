#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/28 09:14:15 by mwelsch           #+#    #+#              #
#    Updated: 2016/03/29 10:34:06 by mwelsch          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = gnl
SRCS = $(shell find . -maxdepth 1 -name "*.c" -type f)
OBJS = $(patsubst %.c,%.o,$(SRCS))
LOBJS = $(patsubst libft/srcs/%.c,libft/objs/%.o,$(shell find libft/srcs -maxdepth 1 -name "*.c" -type f))
CFLAGS=-Wall -Werror -Wextra -g
LDFLAGS=-Llibft/ -lft

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	clang -o $@ $^ #$(LDFLAGS)

libft/libft.a: $(LOBJS)
	@make libft.a --no-print-directory -C libft

%.o: %.c
	clang $(CFLAGS) -c -o $@ $^ -I. -Ilibft/includes

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re all