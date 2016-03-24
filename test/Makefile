TARGET=gnl

UNITS=../get_next_line.c main.c
OBJS=$(patsubst %.c,%.o,$(UNITS))
LIBFT=../libft

LDFLAGS=
DBGFLAGS=
#-ggdb -D_DEBUG
CFLAGS=-I$(LIBFT) -I$(LIBFT)/includes -I./ -I../ -ggdb -Wall -Werror -Wextra -std=c89 $(DBGFLAGS)

CC=clang
LD=$(CC)

all: $(TARGET)

$(TARGET): $(OBJS) $(LIBFT)/libft.a
	@printf "Link %s (%s)\n" "$@" "$^"
	@$(LD) -o $@ $^ $(LDFLAGS)

$(LIBFT)/%.a: lib

lib:
	@make all --no-print-directory -C $(LIBFT)

%.o: %.c
	@printf "Compile '%s':\n" $^
	@$(CC) -o $@ $(CFLAGS) -c $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

run: all
	./$(TARGET)

.PHONY: all re run clean fclean lib lib_d
