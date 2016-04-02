/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 12:17:08 by mwelsch           #+#    #+#             */
/*   Updated: 2016/04/02 15:32:46 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <stdarg.h>

static t_test_suite		g_main_test_suite;
t_test					tests[TEST_COUNT];
static int				g_line_id = 0;

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
	printf("libc: %d: '%s'\n", code, *line);
	if (code > 0)
		return (1);
	else if (code < 0)
		return (-1);
	return (0);
}

int		test_match_string(size_t const n,
						  char const *wanted,
						  char const *got)
{
	static char		lnidbuf[30];
	int strings_match = (wanted && got && !strncmp(wanted, got, n)) || wanted == got;

	snprintf(lnidbuf, 30, "line#%d", g_line_id++);
	log_test(current_test(), "%s: %s (got %zd/%zd chars).", lnidbuf, got, (got ? (ssize_t)strlen(got) : -1), n);
	if (!strings_match)
		ASSERT_TEST(current_test(), strings_match, "strings mismatched: expected '%s', got '%s'.", wanted, got);
	return (!strings_match);
}

int		test_match_return(int wanted, int got)
{
	int return_codes_match = (wanted == got);
	if (!return_codes_match)
		ASSERT_TEST(current_test(), return_codes_match, "returns mismatched: expected '%d', got '%d'.", wanted, got);
	return (!return_codes_match);
}


int		_test_strings(size_t const n,
					  int const nstrs,
					  char const **strs,
					  int (*reader)(int, char**))
{
	g_line_id = 0;
	return (test_strings(n, nstrs, strs, reader, test_match_string, test_match_return));
}

int		test_libc_simple(t_test *test)
{
	static char const *strs[] = {
		"abcdefgh\n",
		"ijklmnop"
	};
	(void)test;
	return (_test_strings(8, 2, strs, libc_get_next_line));
}

int		test_2_lines_of_8(t_test *test)
{
	static char const *strs[] = {
		"abcdefgh\n",
		"ijklmnop"
	};
	(void)test;
	g_line_id = 0;
	return (_test_strings(8, 2, strs, get_next_line));
}

int		test_2_lines_of_16(t_test *test)
{
	static char const *strs[] = {
		"abcdefghijklmnop\n",
		"qrstuvwxyzabcdef\n"
	};
	(void)test;
	g_line_id = 0;
	return (_test_strings(8, 2, strs, get_next_line));
}

int		test_6_lines_of_8(t_test *test)
{
	char const		*strs[]	= {
		"abcdefgh\n",
		"ijklmnop\n",
		"qrstuvwx\n",
		"yzabcdef\n",
		"ghijklmn\n",
		"opqrstuv\n"
	};
	(void)test;
	return (_test_strings(8, 6, strs, get_next_line));
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
	push_test_suite(&g_main_test_suite, "reads 6 lines of 8 chars (with \\n)", test_6_lines_of_8);
	push_test_suite(&g_main_test_suite, "reads 2 lines of 8 chars (no \\n at end)", test_2_lines_of_8);
	push_test_suite(&g_main_test_suite, "reads 2 lines of 16 chars (no \\n at end)", test_2_lines_of_8);
	push_test_suite(&g_main_test_suite, "reads all lines contained in supplied filename", test_openfile);
	push_test_suite(&g_main_test_suite, "reads 2 lines of 8 chars (no \\n at end) (LIBC)", test_libc_simple);
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
