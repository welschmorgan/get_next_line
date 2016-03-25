#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"
int main(void)
{
	char		*line;
	int const	fd = 0;
	int			cmp;

	write(fd, "abcdefgh\n", 9);
	write(fd, "ijklmnop\n", 9);
	get_next_line(fd, &line);
	cmp = strcmp(line, "abcdefgh");
	printf("full line: %s\n", line);
	printf("line 1: %s\n", line);
	printf("\tstrcmp(line, \"abcdefgh\"): %d\n", cmp);
	get_next_line(fd, &line);
	cmp = strcmp(line, "ijklmnop");
	printf("line 2: %s\n", line);
	printf("\tstrcmp(line, \"ijklmnop\"): %d\n", cmp);
}

















