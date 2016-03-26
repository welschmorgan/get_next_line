CFLAGS = -Wall -Wextra -Werror -I../libft/includes -I.. -g
LDFLAGS = -L../libft/ -lft
CC = clang
LD = clang

SHELL=/bin/bash
COUNT=0

SRCS=$(shell find . -name "test_*.c" -type f)
OBJS=$(patsubst %.c,%.o,$(SRCS))
TESTS=$(patsubst %.c,%,$(SRCS))
NOBJS=$(shell echo $(OBJS) | wc -w)

build:
	for TEST in $(TESTS); do $(CC) $(CFLAGS) -c -o $$TEST.o $$TEST.c; done

link:
	for TEST in $(TESTS); do $(LD) -o $$TEST $$TEST.o $(LDFLAGS); done

all: build link
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(TESTS)

re: fclean tests

.PHONY: clean fclean re all build link