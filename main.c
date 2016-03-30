
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 09:20:18 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/30 16:18:01 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int		main(int argc, char *argv[])
{
	int	code;
	int	line;
	int	fd;
	char	*buf;

	fd = open(argc == 2 ? argv[1] : "/dev/stdin", O_RDONLY);
	if (fd < 0)
		return (fd);
	line = 0;
	code = READ_OK;
	while (code > 0)
	{
		code = get_next_line(fd, &buf);
		printf("line#%u[%d]: \"%s\" (%u chars)\n", line, code, buf, (unsigned)(buf ? strlen(buf) : 0));
		line++;
	}
	close(fd);
	return (0);
}
