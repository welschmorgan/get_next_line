/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_2l8c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 11:53:42 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/27 15:53:04 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

int			main(void)
{
	char const	*s1 = "abcdefgh\n";
	char const	*s2 = "ijklmnop\n";
	size_t		l1 = strlen(s1);
	size_t		l2 = strlen(s2);
	int			fd;
	int			c1, c2;
	int			w1, w2;
	char		*buf;

	int		out;
	int		p[2];

	buf = NULL;
	out = dup(1);
	pipe(p);
	fd = 1;
	dup2(p[1], fd);
	w1 = write(fd, s1, l1);
	w2 = write(fd, s2, l2);
	close(p[1]);
	dup2(out, fd);
	printf("write[0]: returned %d / %ld\n", w1, l1);
	printf("write[1]: returned %d / %ld\n", w2, l2);
	get_next_line(p[0], &buf);
	c1 = ft_strncmp(buf, s1, l1 - 1);
	printf("line[0]: %s - compare: %s\n", buf, !c1 ? "OK" : "FAIL");
	if (buf)
		ft_strdel(&buf);
	get_next_line(fd, &buf);
	c2 = ft_strncmp(buf, s2, l2 - 1);
	printf("line[1]: %s - compare: %s\n", buf, !c2 ? "OK" : "FAIL");
	if (buf)
		ft_strdel(&buf);
	close(fd);
	return (0);
}
















