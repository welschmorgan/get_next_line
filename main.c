#include "get_next_line.h"
#include <libft.h>
#include <stdio.h>

static int		g_fd = 0;

int				usage(char const *pname)
{
	printf("usage: %s [fd=0]\n\tfd: an open file descriptor, default is stdin\n", pname);
	return (1);
}


int				loop_ft(char **line)
{
	int			code;
	code = get_next_line(g_fd, line);
	printf("[%d] line: %s\n", code, *line);
	return (code);
}

int				main(void)
{
	int			code;
	char		*line;

	code = READ_OK;
	line = NULL;
	while (code == READ_OK)
	{
		code = loop_ft(&line);
		if (line)
			ft_strdel(&line);
	}
	return (code);
}
