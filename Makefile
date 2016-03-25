NAME=test_gnl

CFLAGS = -Wall -Wextra -Werror -Ilibft/includes -g
LDFLAGS = -Llibft/ -lft
CC = clang
LD = clang

SHELL=/bin/bash
COUNT=0

SRCS=$(shell find . -maxdepth 1 -name "*.c" | grep -v two_lines_of_08)
OBJS=$(patsubst %.c,%.o,$(SRCS))
NOBJS=$(shell echo $(OBJS) | wc -w)

$(NAME): $(OBJS)
	@PRCT=$$( echo "scale=1; $(COUNT) / $(NOBJS) * 100.0" | bc ); \
	printf "\r\033[K[$(CC)|%s%%] Linking $@" "$$PRCT" ; \
	$(LD) $(LDFLAGS) -o $@ $^; \
	printf "\r\033[K[$(CC)|%s%%] Linked $@\n" "$$PRCT";

%.o: %.c
	@PRCT=$$( echo "scale=1; $(COUNT) / $(NOBJS) * 100.0" | bc ); \
	printf "\r\033[K[$(CC)|%s%%] Compiling %s into %s ... " "$$PRCT" "$<" "$@"; \
	$(CC) $(CFLAGS) -c -o $@ $^; \
	$(eval COUNT = $(shell echo "$(COUNT) + 1" | bc) ) \
	printf "\r\033[K[$(CC)|%s%%] Compiled %s into %s ... " "$$PRCT" "$<" "$@"; \

two_lines_of_08.o: two_lines_of_08.c
	gcc -o $@ -c $^ -Ilibft/includes -I. -g

two_lines_of_08: two_lines_of_08.o get_next_line.o
	gcc -o $@ $^ -Llibft -lft

all: $(NAME)

clean:
	@NOBJS=$$(find . -maxdepth 1 -name "*.o" | wc -w); \
	[ $$NOBJS -gt 0 ] && echo "Removing $$NOBJS object(s)."; \
	rm -f $(OBJS);

fclean: clean
	@[ -e $(NAME) ] && echo "Removing target ($(NAME))."; \
	rm -f $(NAME);

re: fclean $(NAME)

.PHONY: clean fclean re all test