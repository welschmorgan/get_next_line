/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 12:17:08 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/31 15:17:51 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>

t_test	tests[TEST_COUNT];

int		test_simple(t_test *test)
{
	int			code;
	char		*s1 = "abcdefgh";
	char		*s2 = "ijklmnop";
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
	if (!gs1 || strncmp(gs1, s1, l1 - 1))
		return (error_test(test, 1, "line[0] should be '%s', got '%s'", s1, gs1));
	printf("line[0] matches '%s'\n", s1);
	if (!gs2 || strncmp(gs2, s2, l2 - 1))
		return (error_test(test, 1, "line[1] should be '%s', got '%s'", s2, gs2));
	printf("line[1] matches '%s'\n", s2);
	if (rs1 != 1)
		return (error_test(test, 1, "line[0] return should have been %d, got %d", 1, rs1));
	if (rs2 != 1)
		return (error_test(test, 1, "line[1] return should have been %d, got %d", 1, rs2));
	if (rs3 != 0)
		return (error_test(test, 1, "line[2] return should have been %d, got %d", 0, rs3));
	return (0);
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

int		init(int argc, char *argv[])
{
	int	i, j;

	printf("%d/%d args allowed!\n", argc, TEST_DATA_SLOTS);
	if (argc >= TEST_DATA_SLOTS)
	{
		printf("only %d args allowed!\n", TEST_DATA_SLOTS);
		return (1);
	}
	init_test(&tests[TEST_SIMPLE], "reads 2 lines of 8 chars (no \\n at end)", test_simple);
	init_test(&tests[TEST_OPEN_FILE], "reads all lines contained in supplied filename", test_openfile);
	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			if (!argv[i])
				continue ;
			printf ("\targv[%d] = '%s' -> user_data[%d]\n", i, argv[i], i - 1);
			j = 0;
			while (j < TEST_COUNT)
				tests[j++].user_data[i - 1] = argv[i];
			i++;
		}
	}
	return (0);
}

int		reset(void)
{
	reset_test(&tests[TEST_SIMPLE]);
	reset_test(&tests[TEST_OPEN_FILE]);
	return (0);
}

int		run()
{
	int	code;

	code = 0;
	code += run_test(&tests[TEST_SIMPLE]);
	code += run_test(&tests[TEST_OPEN_FILE]);
	return (code);

}

int		main(int argc, char *argv[])
{
	int		code;

	code = init(argc, argv);
	if (code)
		return (code);
	code += run();
	code += reset();
	return (code);
}
