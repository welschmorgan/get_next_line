/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 12:17:08 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/31 11:03:41 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.h"
# include <time.h>

t_test	tests[TEST_COUNT];

int		test_dummy(t_test *test)
{
	printf("* starting test \"%s\"\n", test->name);
	return (0);
}

int		init(void)
{
	int	code;

	code = 0;
	init_test(&tests[TEST_DUMMY], "dummy template test", test_dummy);
	return (code);
}

int		reset(void)
{
	reset_test(&tests[TEST_DUMMY]);
	return (0);
}

int		run()
{
	int	code;

	code = 0;
	code += run_test(&tests[TEST_DUMMY]);
	return (code);

}

int		main(void)
{
	int		code;

	code = init();
	code += run();
	code += reset();
	return (code);
}
