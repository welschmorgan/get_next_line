#include "testing.h"
#include "assert.h"

void	test_line(int const fd, char **line, char const *should_be)
{
	int c;
	c = get_next_line(fd, line);
	printf("line[%d]: %s\n", c, *line);
	if (*line)
		assert(strcmp(*line, should_be) == 0);
	printf("\tOK\n");
}

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
	test_line(p[0], &line, "abcdefgh");
	test_line(p[0], &line, "ijklmnop");
	test_line(p[0], &line, "qrstuvwx");
	test_line(p[0], &line, "yzabcdef");
	test_line(p[0], &line, "ghijklmn");
	test_line(p[0], &line, "opqrstuv");
	test_line(p[0], &line, "wxyzabcd");
	test_line(p[0], &line, "");
	close(fd);
	close(out);
	close(p[0]);
	return (0);
}









