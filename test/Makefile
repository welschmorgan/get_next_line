INC_DIR=includes
SRC_DIR=units
OBJ_DIR=objs

CFLAGS = -Wall -Wextra -Werror -I../libft/includes -I.. -I$(INC_DIR) -g
LDFLAGS = -L../libft/ -lft
CC = clang
LD = clang

SHELL=/bin/bash
COUNT=0

SRCS=$(shell find $(SRC_DIR) -name "test_*.c" -type f)
OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TESTS=$(patsubst $(SRC_DIR)/%.c,%,$(SRCS))
NOBJS=$(shell echo $(OBJS) | wc -w)

all: $(OBJS) $(OBJ_DIR)/get_next_line.o $(TESTS)

test_%: $(OBJ_DIR)/get_next_line.o $(OBJ_DIR)/test_%.o
	$(LD) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/get_next_line.o: ../get_next_line.c
	$(CC) -c -o $@ $^ $(CFLAGS)

$(OBJ_DIR)/test_%.o: $(SRC_DIR)/test_%.c
	$(CC) -c -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJS) $(OBJ_DIR)/get_next_line.o
fclean: clean
	rm -f $(TESTS)
re: fclean all

.PHONY: clean fclean re all