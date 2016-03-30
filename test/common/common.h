/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 13:37:45 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/30 14:53:44 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		COMMON_H
# define	COMMON_H

# include <stdlib.h>
# include "libft.h"

# define TEST_NAME_SIZE		20
# define TEST_ERROR_SIZE	180

struct			s_test;
typedef int		(*t_test_fn)(struct s_test *);

typedef struct	s_test
{
	char		name[TEST_NAME_SIZE];
	char		error[TEST_ERROR_SIZE];
	t_test_fn	func;
	int			code;
}				t_test;

int				run_test(t_test *test);
int				init_test(t_test *test, char const *name, t_test_fn fn);
int				error_test(t_test *test, int code, char const *fmt, ...);

#endif



















