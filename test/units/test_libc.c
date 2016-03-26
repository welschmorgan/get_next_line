/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 12:57:28 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/26 13:46:08 by mwelsch          ###   ########.fr       */
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
	char			*lnbuf;
	int				code;
	int				line;
	size_t			lncap;
	int				fd;
	FILE			*f;

	fd = STDIN_FILENO;
	f = fdopen(fd, "rw+");
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
		fprintf(f, "%s\n", *pline);
		pline++;
	}
	fflush(f);
	lnbuf = NULL;
	lncap = 0;
	line = 0;
	code = 1;
	while (code > 0)
	{
		code = getline(&lnbuf, &lncap, f);
		if (lnbuf)
			printf("line[%d]: \"%s\" (%ld chars)\n", line, lnbuf, strlen(lnbuf));
		if (lnbuf)
			ft_strdel(&lnbuf);
		line++;
	}
	printf("on exit, line pointer is %p\n", lnbuf);
	fclose(f);
	return (0);
}
