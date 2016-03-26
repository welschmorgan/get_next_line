/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 14:59:47 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/26 15:06:50 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"
#include <stdio.h>
#include <unistd.h>

void	feed_input(int fd)
{
	char const		*buf[] =
		{
			"this is the first line of a small file",
			"and this is the second one",
			"",
			"the line above should be blank as well as the",
			"one below.",
			"",
			NULL
		};
	char const		**pline;

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
}
