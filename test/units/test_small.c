/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 12:57:28 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/27 13:46:54 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "testing.h"

int		main(void)
{
	int		line;
	int		code;
	char	*lnbuf;

	feed_input(STDIN_FILENO);
	line = 0;
	code = 1;
	while (code > 0)
	{
		code = get_next_line(STDIN_FILENO, &lnbuf);
		printf("line[%d]: \"%s\" (%ld chars)\n", line, lnbuf, strlen(lnbuf));
		if (lnbuf)
			ft_strdel(&lnbuf);
		line++;
	}
	if (lnbuf)
		ft_strdel(&lnbuf);
	printf("on exit, line pointer is %p\n", lnbuf ? lnbuf : (char*)NULL);
	return (0);
}
