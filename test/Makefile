CFLAGS = -Wall -Wextra -Werror -I. -I.. -I../libft/includes -Icommon -g
LDFLAGS = -L../libft/ -lft

CC = clang
LD = $(CC)

SHELL=/bin/bash
COUNT=0

HDRS=$(shell find . -maxdepth 1 -name "*.h") $(shell find common -maxdepth 1 -name "*.h")
SRCS=$(shell find . -maxdepth 1 -name "*.c")
CSRCS=$(shell find common -maxdepth 1 -name "*.c")
OBJS=$(patsubst %.c,%.o,$(SRCS))
COBJS=$(patsubst %.c,%.o,$(CSRCS))
APPS=$(patsubst %.c,%.run,$(SRCS))
NOBJS=$(shell echo $(OBJS) | wc -w)

common/%.o: common/%.c
	@PRCT=$$( echo "scale=1; $(COUNT) / $(NOBJS) * 100.0" | bc ); \
	printf "\r\033[K[$(CC)|%s%%] Compiling %s into %s ... " "$$PRCT" "$<" "$@"; \
	$(CC) $(CFLAGS) -c -o $@ $^; \
	$(eval COUNT = $(shell echo "$(COUNT) + 1" | bc) ) \
	printf "\r\033[K[$(CC)|%s%%] Compiled %s into %s ... " "$$PRCT" "$<" "$@"; \

%.o: %.c
	@PRCT=$$( echo "scale=1; $(COUNT) / $(NOBJS) * 100.0" | bc ); \
	printf "\r\033[K[$(CC)|%s%%] Compiling %s into %s ... " "$$PRCT" "$<" "$@"; \
	$(CC) $(CFLAGS) -c -o $@ $^; \
	$(eval COUNT = $(shell echo "$(COUNT) + 1" | bc) ) \
	printf "\r\033[K[$(CC)|%s%%] Compiled %s into %s ... " "$$PRCT" "$<" "$@"; \

%.run: %.o $(COBJS)
	@PRCT=$$( echo "scale=1; $(COUNT) / $(NOBJS) * 100.0" | bc ); \
	printf "\r\033[K[$(CC)|%s%%] Linking $@" "$$PRCT" ; \
	$(LD) -o $@ $^ $(LDFLAGS) ; \
	printf "\r\033[K[$(CC)|%s%%] Linked $@\n" "$$PRCT";

all: $(COBJS) $(OBJS) $(APPS)

clean:
	@NOBJS=$$(find . -name "*.o" | wc -w); \
	[ $$NOBJS -gt 0 ] && echo "Removing $$NOBJS object(s)."; \
	rm -f $(OBJS) $(COBJS);

fclean: clean
	@NAPPS=$$(find . -name "*.run" | wc -w); \
	[ $$NAPPS -gt 0 ] && echo "Removing $$NAPPS target(s)."; \
	rm -f $(APPS)

re: fclean $(APPS)

.PHONY: clean fclean re all