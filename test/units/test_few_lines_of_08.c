#include "testing.h"
#include "assert.h"

int main(void)
{
	char 	*line;
	int		out;
	int		p[2];
	int		fd;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abcdefgh\n", 9);
	write(fd, "ijklmnop\n", 9);
	write(fd, "qrstuvwx\n", 9);
	write(fd, "yzabcdef\n", 9);
	write(fd, "ghijklmn\n", 9);
	write(fd, "opqrstuv\n", 9);
	write(fd, "wxyzabcd\n", 9);
	close(p[1]);
	dup2(out, fd);
	get_next_line(p[0], &line);
	assert(strcmp(line, "abcdefgh") == 0);
	get_next_line(p[0], &line);
	assert(strcmp(line, "ijklmnop") == 0);
	get_next_line(p[0], &line);
	assert(strcmp(line, "qrstuvwx") == 0);
	get_next_line(p[0], &line);
	assert(strcmp(line, "yzabcdef") == 0);
	get_next_line(p[0], &line);
	assert(strcmp(line, "ghijklmn") == 0);
	get_next_line(p[0], &line);
	assert(strcmp(line, "opqrstuv") == 0);
	get_next_line(p[0], &line);
	assert(strcmp(line, "wxyzabcd") == 0);
	return (0);
}









