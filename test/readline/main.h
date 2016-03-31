/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 14:04:19 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/31 12:26:54 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		READLINE_H
# define	READLINE_H

#include "libft.h"
#include "common.h"
#include <stdio.h>

int				test_openfile(t_test *test);
int				test_simple(t_test *test);

typedef enum	e_test_data_id
{
	TEST_DATA_PATH,
	TEST_DATA_COUNT
}				t_test_data_id;

typedef enum	e_test_id
{
	TEST_SIMPLE,
	TEST_OPEN_FILE,
	TEST_COUNT
}				t_test_id;

#endif
