/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 12:17:08 by mwelsch           #+#    #+#             */
/*   Updated: 2016/04/01 13:41:36 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>

static t_test_suite		g_main_test_suite;
t_test					tests[TEST_COUNT];

int		libc_get_next_line(int const fd, char **line)
{
	size_t			linecapp = 0;
	FILE			*file;
	int				code;
	file = fdopen(fd, "r");
	if (!file)
		return (-1);
	*line = NULL;
	code = getline(line, &linecapp, file);
	ft_strrtrim(*line, "\n");
	if (code > 0)
		return (1);
	else if (code < 0)
		return (-1);
	return (0);
}

int		validate_read(t_test *test, char const *prefix,
					  char *s_read, char *s_libc,
					  int const c_read, int const c_libc)
{
	int	str = ((s_libc && s_read && !strcmp(s_libc, s_read)) || s_read == s_libc);
	int code = (c_read == c_libc);

	log_test(test, "%s: %s.", prefix, s_read);
	if (!str)
		return (error_test(test, 1, "string mismatch: %s: expected '%s' but got '%s'.", prefix, s_libc, s_read));
	if (!code)
		return (error_test(test, 1, "return mismatch: %s: expected %d but got %d.", prefix, c_libc, c_read));
	return (0);
}

int		test_libc_simple(t_test *test)
{
	int			code;
	char		*s1 = "abcdefgh";
	char		*s2 = "ijklmnop";
	char		*s3 = NULL;
	size_t const l1 = strlen(s1);
	size_t const l2 = strlen(s2);
	char		*gs1 = NULL, *gs2 = NULL, *gs3 = NULL;
	int			rs1, rs2, rs3;

	if ((code = open_pipe()))
		return (code);
	write_pipe(s1, l1);
	write_pipe("\n", 1);
	write_pipe(s2, l2);
	write_pipe("\n", 1);
	close(g_pipe_fd[1]);
	rs1 = read_pipe(&gs1, libc_get_next_line);
	rs2 = read_pipe(&gs2, libc_get_next_line);
	rs3 = read_pipe(&gs3, libc_get_next_line);
	close(g_pipe_fd[0]);
	code = 0;
	if (!code)
		code = validate_read(test, "line#0", gs1, s1, rs1, 1);
	if (!code)
		code = validate_read(test, "line#1", gs2, s2, rs2, 1);
	if (!code)
		code = validate_read(test, "line#2", gs3, s3, rs3, 0);
	ft_strdel(&gs1);
	ft_strdel(&gs2);
	ft_strdel(&gs3);
	return (code);
}

int		test_simple(t_test *test)
{
	int			code;
	char		*s1 = "abcdefgh";
	char		*s2 = "ijklmnop";
	char		*s3 = NULL;
	size_t const l1 = strlen(s1);
	size_t const l2 = strlen(s2);
	char		*gs1, *gs2, *gs3;
	int			rs1, rs2, rs3;

	if ((code = open_pipe()))
		return (code);
	write_pipe(s1, l1);
	write_pipe("\n", 1);
	write_pipe(s2, l2);
	write_pipe("\n", 1);
	close(g_pipe_fd[1]);
	rs1 = read_pipe(&gs1, get_next_line);
	rs2 = read_pipe(&gs2, get_next_line);
	rs3 = read_pipe(&gs3, get_next_line);
	close(g_pipe_fd[0]);
	code = 0;
	if (!code)
		code = validate_read(test, "line#0", gs1, s1, rs1, 1);
	if (!code)
		code = validate_read(test, "line#1", gs2, s2, rs2, 1);
	if (!code)
		code = validate_read(test, "line#2", gs3, s3, rs3, 0);
	ft_strdel(&gs1);
	ft_strdel(&gs2);
	ft_strdel(&gs3);
	return (code);
}

int		test_openfile(t_test *test)
{
	int	code;
	int	line;
	int	fd;
	char	*buf;
	char const	*path;

	path = (test->user_data[TEST_DATA_PATH] ? ((char const *)test->user_data[TEST_DATA_PATH]) : ((char const *)"/dev/stdin"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_test(test, 1, "%s: cannot open file!\n", path));
	printf("* opened \"%s\", fd#%d\n", path, fd);
	line = 0;
	code = 1;
	while (code > 0)
	{
		code = get_next_line(fd, &buf);
		printf("line#%u[%d]: \"%s\" (%u chars)\n", line, code, buf, (unsigned)(buf ? strlen(buf) : 0));
		line++;
	}
	close(fd);
	return (0);
}

int		init(int argc, char const *argv[])
{
	if (argc >= TEST_DATA_SLOTS)
	{
		printf("only %d args allowed!\n", TEST_DATA_SLOTS);
		return (1);
	}
	if (init_test_suite(&g_main_test_suite, "tests.log", argc, argv))
		return (1);
	push_test_suite(&g_main_test_suite, "reads 2 lines of 8 chars (no \\n at end) (LIBC)", test_libc_simple);
	push_test_suite(&g_main_test_suite, "reads 2 lines of 8 chars (no \\n at end)", test_simple);
	push_test_suite(&g_main_test_suite, "reads all lines contained in supplied filename", test_openfile);
	return (0);
}

int		reset(void)
{
	reset_test_suite(&g_main_test_suite);
	return (0);
}

int		run()
{
	return (run_test_suite(&g_main_test_suite));

}

int		main(int argc, char const *argv[])
{
	int		code;

	code = init(argc, argv);
	if (code)
		return (code);
	code += run();
	code += reset();
	return (code);
}
