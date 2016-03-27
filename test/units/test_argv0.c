/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 12:57:28 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/27 14:19:48 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"
#include <fcntl.h>
#include <stdio.h>

//static FILE	*g_file = NULL;
static int	g_fd = -1;

static int	read_ft(char **buf)
{
	return (get_next_line(g_fd, buf));
}

/*static int	read_libc(char **buf)
{
	static size_t	size = 0;
	return (getline(buf, &size, g_file));
}
*/
static int	pass(char const *name, int (*pfn)(char **buf), char **lnbuf)
{
	int		line;
	int		code;

	*lnbuf = NULL;
	line = 0;
	code = 1;
	while (code > 0)
	{
		code = pfn(lnbuf);
		printf("%s - line[%d]: \"%s\" (%ld chars)\n", name, line, *lnbuf ? *lnbuf : "NULL", *lnbuf ? strlen(*lnbuf) : 0);
		if (*lnbuf)
			ft_strdel(lnbuf);
		line++;
	}
	if (*lnbuf)
		ft_strdel(lnbuf);
	printf("on exit, line pointer is %p\n", *lnbuf ? *lnbuf : (char *)NULL);
	return (0);
}

int		main(int argc, char *argv[])
{
	int		ft_ret;
	//int		libc_ret;
	char	*line;

	if (argc != 2)
		return (1);
	g_fd = open(argv[1], O_RDONLY);
	if (g_fd < 0)
		return (2);
	ft_ret = pass("libft", read_ft, &line);
	close(g_fd);
	/*g_file = fdopen(g_fd, "r");
	libc_ret = pass("libc", read_libc, &line);
	fclose(g_file);*/
}
