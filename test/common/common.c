/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 13:40:24 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/30 15:32:18 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"
#include <stdio.h>
#include <stdarg.h>

t_test			*g_test = NULL;

int				init_test(t_test *test, char const *name, t_test_fn fn)
{
	if (!test)
		return (1);
	strncpy(test->name, name, TEST_NAME_SIZE);
	strncpy(test->error, "", TEST_ERROR_SIZE);
	test->func = fn;
	test->code = 0;
	test->signal = -1;
	install_test_sighandler(test, SIGINT, signal_test);
	install_test_sighandler(test, SIGQUIT, signal_test);
	install_test_sighandler(test, SIGKILL, signal_test);
	install_test_sighandler(test, SIGILL, signal_test);
	install_test_sighandler(test, SIGBUS, signal_test);
	install_test_sighandler(test, SIGSEGV, signal_test);
	return (test->code);
}

void			install_test_sighandler(t_test *test, int sigc, sig_t func)
{
	test->signal_handler[sigc] = signal(sigc, func);
}

void			uninstall_test_sighandler(t_test *test, int sigc)
{
	signal(sigc, test->signal_handler[sigc]);
}

int				reset_test(t_test *test)
{
	uninstall_test_sighandler(test, SIGINT);
	uninstall_test_sighandler(test, SIGQUIT);
	uninstall_test_sighandler(test, SIGKILL);
	uninstall_test_sighandler(test, SIGILL);
	uninstall_test_sighandler(test, SIGBUS);
	uninstall_test_sighandler(test, SIGSEGV);
	return (0);
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

void			signal_test(int sigc)
{
	if (g_test)
		g_test->signal = sigc;
}

int				run_test(t_test *test)
{
	if (!test)
		return (1);
	static char	hline[80] = {0};

	g_test = test;
	if (!hline[0])
		memset(&hline[0], '-', 80);
	memset(&test->error[0], 0, TEST_ERROR_SIZE);
	printf("%s\n* Starting test '%s':\n", hline, test->name);
	test->signal = -1;
	test->code = test->func(test);
	if (test->signal > 0)
		printf("\nsignal: %i\n", test->signal);
	if (test->code)
		printf("\nreturned: %i -> %s\n", test->code, test->error);
	return (test->code);
}
