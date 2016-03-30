/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 13:37:45 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/30 15:29:55 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		COMMON_H
# define	COMMON_H

# include <stdlib.h>
# include <signal.h>
# include "libft.h"

# define TEST_NAME_SIZE		20
# define TEST_ERROR_SIZE	180
# define TEST_SIGC_NUM		31

struct			s_test;
typedef int		(*t_test_fn)(struct s_test *);

typedef struct	s_test
{
	char		name[TEST_NAME_SIZE];
	char		error[TEST_ERROR_SIZE];
	t_test_fn	func;
	int			code;
	int			signal;
	sig_t		signal_handler[TEST_SIGC_NUM + 1];
}				t_test;

extern t_test	*g_test;

int				init_test(t_test *test, char const *name, t_test_fn fn);
int				reset_test(t_test *test);

void			signal_test(int sigc);

void			install_test_sighandler(t_test *test, int sigc, sig_t func);
void			uninstall_test_sighandler(t_test *test, int sigc);

int				run_test(t_test *test);

int				error_test(t_test *test, int code, char const *fmt, ...);

#endif



















