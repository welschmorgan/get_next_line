/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 12:17:08 by mwelsch           #+#    #+#             */
/*   Updated: 2016/04/02 14:49:49 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "strjoin.h"
# include <time.h>

t_test_suite	g_main_test_suite;
static char		g_buf[1024] = {0};

int		test_join(char const *s1, char const *s2)
{
	char	*joined;
	int		joined_string_matches;
	int		code;

	snprintf(g_buf, 1024, "%s%s", s1, s2);
	joined = ft_strjoin(s1, s2);
	joined_string_matches = !strcmp(joined, g_buf);
	code = ASSERT_TEST(current_test(), joined_string_matches, "string mismatch: joined '%s' + '%s', expected '%s', got '%s'.", s1, s2, g_buf, joined);
	if (!code)
		log_test(current_test(), "string joined: '%s' + '%s' = '%s'.", s1, s2, joined);
	return (code);
}

int		test_join_2_str_8_chars(t_test *t)
{
	(void)t;
	return (test_join("abcdefgh", "ijklmnop"));
}

int		test_join_2_str_0_chars(t_test *t)
{
	(void)t;
	static char const	*strs[] = {
		"", "",
		NULL, NULL
	};
	char const			**pstr;
	int					code;
	pstr = &strs[0];
	code = 0;
	while (pstr && *pstr)
	{
		code += test_join(*pstr, *(pstr + 1));
		pstr += 2;
	}
	return (code);
}

int		test_join_6_str_8_chars(t_test *t)
{
	(void)t;
	static char const	*strs[] = {
		"abcdefgh", "ijklmnop",
		"qrstuvwx", "yz012345",
		"67890abc", "defghijk",
		NULL, NULL
	};
	char const			**pstr;
	int					code;
	pstr = &strs[0];
	code = 0;
	while (pstr && *pstr)
	{
		code += test_join(*pstr, *(pstr + 1));
		pstr += 2;
	}
	return (code);
}

int		init(int argc, char const *argv[])
{
	int	code;

	code = 0;
	init_test_suite(&g_main_test_suite, "tests.log", argc, argv);
	push_test_suite(&g_main_test_suite, "joins two 8 chars strings", test_join_2_str_8_chars);
	push_test_suite(&g_main_test_suite, "joins 3 times two 8 chars strings", test_join_6_str_8_chars);
	push_test_suite(&g_main_test_suite, "joins two empty strings", test_join_2_str_0_chars);
	return (code);
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
	code += run();
	code += reset();
	return (code);
}
