/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 14:04:19 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/30 14:05:06 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		DLIST_H
# define	DLIST_H

#include "libft.h"
#include "common.h"
#include <stdio.h>

int				test_dlist_add5(t_test *test);
int				test_dlist_deltail5(t_test *test);
int				test_dlist_delhead5(t_test *test);
int				test_dlist_delrand5(t_test *test);
int				test_dlist_clear(t_test *test);

typedef enum	e_dlist_test
{
	DLIST_ADD5,
	DLIST_DELTAIL5,
	DLIST_DELHEAD5,
	DLIST_CLEAR,
	DLIST_DELRAND5,
	DLIST_COUNT
}				t_dlist_test;

extern t_dlist	g_list;

#endif
