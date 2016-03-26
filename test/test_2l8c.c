/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_2l8c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 11:53:42 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/26 11:58:36 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int			main(void)
{
	char const	*s1 = "abcdefgh";
	char const	*s2 = "ijklmnop";
	int			fd;
	int			c1, c2;
	char		*buf;

	fd = dup(0);
	ft_putendl_fd(s1, fd);
	ft_putendl_fd(s2, fd);
	get_next_line(fd, &buf);
	c1 = ft_strcmp(buf, s1);
	printf("line[0]: %s - compare: %s\n", buf, !c1 ? "OK" : "FAIL");
	get_next_line(fd, &buf);
	c2 = ft_strcmp(buf, s2);
	printf("line[1]: %s - compare: %s\n", buf, !c2 ? "OK" : "FAIL");
	close(fd);
	return (0);
}
















