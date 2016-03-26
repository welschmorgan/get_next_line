INC_DIR=includes
SRC_DIR=units
OBJ_DIR=objs
LIB_DIR=../libft

CFLAGS = -Wall -Wextra -Werror -I../libft/includes -I.. -I$(INC_DIR) -Icommon -g
LDFLAGS = -L../libft/ -lft
CC = clang
LD = clang

SHELL=/bin/bash
COUNT=0

SRCS=$(shell find $(SRC_DIR) -name "test_*.c" -type f)
OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TESTS=$(patsubst $(SRC_DIR)/%.c,%,$(SRCS))
NOBJS=$(shell echo $(OBJS) | wc -w)

all: $(OBJS) $(OBJ_DIR)/get_next_line.o $(OBJ_DIR)/testing.o $(LIB_DIR)/libft.a $(TESTS)

test_%: $(OBJ_DIR)/get_next_line.o $(OBJ_DIR)/testing.o $(OBJ_DIR)/test_%.o
	$(LD) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/get_next_line.o: ../get_next_line.c
	@if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi
	$(CC) -c -o $@ $^ $(CFLAGS)

$(OBJ_DIR)/testing.o: common/testing.c
	@if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi
	$(CC) -c -o $@ $^ $(CFLAGS)

$(OBJ_DIR)/test_%.o: $(SRC_DIR)/test_%.c
	@if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi
	$(CC) -c -o $@ $^ $(CFLAGS)

$(LIB_DIR)/libft.a:
	make -C $(LIB_DIR)

clean:
	rm -f $(OBJS) $(OBJ_DIR)/get_next_line.o
fclean: clean
	rm -f $(TESTS)
re: fclean all

.PHONY: clean fclean re all