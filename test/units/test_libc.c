/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 12:57:28 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/27 12:23:00 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

int		main(void)
{
	char	*lnbuf;
	size_t	lncap;
	int		line;
	int		code;

	feed_input(STDIN_FILENO);
	lnbuf = NULL;
	lncap = 0;
	line = 0;
	code = 1;
	FILE	*f;

	f = fdopen(STDIN_FILENO, "rw+");
	if (!f)
	{
		perror("failed to open file!");
		return (1);
	}
	while (code > 0)
	{
		code = getline(&lnbuf, &lncap, f);
		if (lnbuf)
			printf("line[%d]: \"%s\" (%ld chars)\n", line, lnbuf, strlen(lnbuf));
		if (lnbuf)
			ft_strdel(&lnbuf);
		line++;
	}
	if (lnbuf)
		ft_strdel(&lnbuf);
	printf("on exit, line pointer is %p\n", lnbuf);
	fclose(f);
	return (0);
}
