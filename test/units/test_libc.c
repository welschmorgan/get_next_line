/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 12:57:28 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/26 13:28:16 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

int		main(void)
{
	char const		*buf[] =
		{
			"this is the first line of a small file",
			"and this is the second one",
			"",
			"the line above should be blank as well as the",
			"one below.",
			NULL
		};
	char const		**pline;
	char			lnbuf[100];
	int				code;
	int				line;
	int				fd;

	fd = dup(STDIN_FILENO);
	pline = &buf[0];
	printf("Input buffer (%ld)\n-------------\n", sizeof(buf) / sizeof(char const *) - 1);
	while (*pline)
	{
		printf("%ld chars -\t\"%s\"\n", strlen(*pline), *pline);
		pline++;
	}
	pline = &buf[0];
	while (*pline)
	{
		ft_putendl_fd(*pline, fd);
		pline++;
	}
	fflush(stdin);
	fflush(stdout);
	line = 0;
	code = 1;
	while (code > 0)
	{
		code = read(fd, &lnbuf[0], 100);
		printf("line[%d]: \"%s\" (%ld chars)\n", line, lnbuf, strlen(lnbuf));
		line++;
	}
	printf("on exit, line pointer is %p\n", lnbuf);
	return (0);
}
