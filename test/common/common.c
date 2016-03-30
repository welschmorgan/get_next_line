/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 13:40:24 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/30 14:53:07 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"
#include <stdio.h>
#include <stdarg.h>

int				init_test(t_test *test, char const *name, t_test_fn fn)
{
	if (!test)
		return (1);
	ft_strncpy(test->name, name, TEST_NAME_SIZE);
	test->func = fn;
	test->code = 0;
	return (test->code);
}

int				error_test(t_test *test, int code, char const *fmt, ...)
{
	va_list		args;

	va_start(args, fmt);
	vsnprintf(test->error, TEST_ERROR_SIZE, fmt, args);
	va_end(args);
	test->code = code;
	return (code);
}

int				run_test(t_test *test)
{
	if (!test)
		return (1);
	static char	hline[80] = {0};

	if (!hline[0])
		memset(&hline[0], '-', 80);
	memset(&test->error[0], 0, TEST_ERROR_SIZE);
	printf("%s\n* Starting test '%s':\n", hline, test->name);
	test->code = test->func(test);
	if (test->code)
		printf("\nreturned: %i -> %s\n", test->code, test->error);
	return (test->code);
}
