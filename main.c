/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 09:20:18 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/30 12:19:02 by mwelsch          ###   ########.fr       */
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
	while ((code = get_next_line(fd, &buf)) > 0)
	{
		printf("line#%u[%d]: \"%s\" (%u chars)\n", line, code, buf, (unsigned)strlen(buf));
		line++;
	}
	close(fd);
	return (0);
}
