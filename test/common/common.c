/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 13:40:24 by mwelsch           #+#    #+#             */
/*   Updated: 2016/04/01 13:51:51 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>

static t_test_suite	*g_test_suite = NULL;
int					g_pipe_fd[2];

t_test			*current_test()
{
	return (g_test_suite && g_test_suite->current ? g_test_suite->current : NULL);
}

int				open_pipe()
{
	int		code;

	if ((code = pipe(g_pipe_fd)) != 0)
		return (code);
	if (g_pipe_fd[0] < 0 || g_pipe_fd[1] < 0)
		return (1);
	return (0);
}

int				write_pipe(char const *str, size_t const n)
{
	return (write(g_pipe_fd[1], str, n));
}

int				read_pipe(char **line, int(*fn)(int, char **))
{
	return (fn(g_pipe_fd[0], line));
}

int				init_test(t_test *test, t_test_suite *suite, char const *name, t_test_fn fn)
{
	if (!test)
		return (1);
	strncpy(test->name, name, TEST_NAME_SIZE);
	strncpy(test->error, "", TEST_ERROR_SIZE);
	memset(test->user_data, 0, sizeof(void*) * TEST_DATA_SLOTS);
	test->suite = suite;
	test->log_fd = suite->log_fd;
	test->func = fn;
	test->code = 0;
	test->signal = -1;
	return (test->code);
}

void			signal_test_suite(int sigc)
{
	if (g_test_suite && g_test_suite->current)
		g_test_suite->current->signal = sigc;
}

void			install_test_suite_sighandler(t_test_suite *test, int sigc, sig_t func)
{
	test->signal_handler[sigc] = signal(sigc, func);
}

void			uninstall_test_suite_sighandler(t_test_suite *test, int sigc)
{
	signal(sigc, test->signal_handler[sigc]);
}

int				reset_test(t_test *test)
{
	(void)test;
	return (0);
}

int				error_test(t_test *test, int code, char const *fmt, ...)
{
	va_list		args;
	size_t		len;

	va_start(args, fmt);
	vsnprintf(test->error, TEST_ERROR_SIZE, fmt, args);
	va_end(args);
	test->code = code;
	len = strlen(test->error);
	ft_strrtrim(test->error, "\n");
	if (test->log_fd > 0)
	{
		write(test->log_fd, "[error] ", 8);
		write(test->log_fd, test->error, len);
		write(test->log_fd, "\n", 1);
	}
	if (test->log_fd != 2)
	{
		write(2, "[error] ", 8);
		write(2, test->error, len);
		write(2, "\n", 1);
	}
	return (code);
}


int				log_test(t_test *test, char const *fmt, ...)
{
	char		buf[1024];
	va_list		args;
	size_t		len;

	va_start(args, fmt);
	vsnprintf(buf, 1024, fmt, args);
	va_end(args);
	len = strlen(buf);
	if (buf[len] != '\n')
		strcpy(&buf[len], "\n");
	if (test->log_fd >= 0)
		write(test->log_fd, buf, len + 1);
	if (test->log_fd != 1)
		write(1, buf, len + 1);
	return (test->code);
}

int				run_test(t_test *test)
{
	if (!test)
		return (1);
	static char	hline[80] = {0};

	if (!hline[0])
		memset(&hline[0], '-', 80);
	memset(&test->error[0], 0, TEST_ERROR_SIZE);
	log_test(test, "%s\n* Starting test '%s':", hline, test->name);
	test->signal = -1;
	test->code = test->func(test);
	if (test->signal > 0)
		log_test(test, "\nsignal: %i", test->signal);
	if (test->code)
		log_test(test, "\nreturned: %i -> %s", test->code, test->error);
	return (test->code);
}

void		print_tests_results(t_test const *tests, size_t n)
{
	t_test const	*ptest;
	printf("** Tests Results:");
	while (n)
	{
		ptest = &tests[n];
		printf("*\ttest[%ld]: %s\n\t-> return:%d\terror:\"%s\"\tsignal:%d\n", n, ptest->name, ptest->code, ptest->error, ptest->signal);
		n--;
	}
}

int				init_test_suite(t_test_suite *suite, char const *log_name, int argc, char const *argv[])
{
	int	i;

	if (!suite)
		return (1);
	suite->log_fd = log_name ? open(log_name, O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, S_IWRITE | S_IREAD) : -1;
	if (log_name && suite->log_fd < 0)
		return (suite->log_fd);
	g_test_suite = suite;
	memset(suite->user_data, 0, sizeof(void*) * TEST_DATA_SLOTS);
	install_test_suite_sighandler(suite, SIGINT, signal_test_suite);
	install_test_suite_sighandler(suite, SIGQUIT, signal_test_suite);
	install_test_suite_sighandler(suite, SIGKILL, signal_test_suite);
	install_test_suite_sighandler(suite, SIGILL, signal_test_suite);
	install_test_suite_sighandler(suite, SIGBUS, signal_test_suite);
	install_test_suite_sighandler(suite, SIGSEGV, signal_test_suite);
	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			if (!argv[i])
				continue ;
			printf ("argv[%d] = '%s' -> user_data[%d]\n", i, argv[i], i - 1);
			suite->user_data[i - 1] = (void*)argv[i];
			i++;
		}
	}
	suite->current = NULL;
	suite->code = 0;
	suite->start_time = time(NULL);
	suite->end_time = suite->start_time;
	ft_dlist_init(&suite->tests);
	return (0);
}

t_test			*push_test_suite(t_test_suite *suite, char const *name, t_test_fn func)
{
	int j;
	t_test *test;

	if (!suite)
		return (NULL);
	if (!(test = malloc(sizeof(t_test))))
		return (test);
	init_test(test, suite, name, func);
	ft_dlist_add_back(&suite->tests, ft_dnode_new(test, sizeof(t_test), NF_DESTROY_ALL));
	j = 0;
	while (j < TEST_DATA_SLOTS)
	{
		test->user_data[j] = suite->user_data[j];
		j++;
	}
	return (test);
}

int				run_test_suite(t_test_suite *suite)
{
	t_dnode		*node;

	suite->code = 0;
	node = suite->tests.tail;
	suite->start_time = time(NULL);
	suite->end_time = suite->start_time;
	while (node)
	{
		suite->current = (t_test*)node->data;
		suite->code += run_test(suite->current);
		node = node->next;
	}
	suite->end_time = time(NULL);
	return (suite->code);
}

void			reset_test_suite(t_test_suite *suite)
{
	if (!suite)
		return ;
	t_dnode		*node;
	node = suite->tests.tail;
	while (node)
	{
		reset_test((t_test*)node->data);
		node = node->next;
	}
	uninstall_test_suite_sighandler(suite, SIGINT);
	uninstall_test_suite_sighandler(suite, SIGQUIT);
	uninstall_test_suite_sighandler(suite, SIGKILL);
	uninstall_test_suite_sighandler(suite, SIGILL);
	uninstall_test_suite_sighandler(suite, SIGBUS);
	uninstall_test_suite_sighandler(suite, SIGSEGV);
	if (suite->log_fd >= 0)
	{
		suite->code = 0;
		close(suite->log_fd);
		suite->log_fd = -1;
	}
	ft_dlist_clear(&suite->tests, ft_dlist_deleter);
}

t_test_suite			*current_test_suite()
{
	return (g_test_suite);
}
