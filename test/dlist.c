/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 12:17:08 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/30 14:58:12 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "dlist.h"
# include <time.h>

t_dlist	g_list;

void	print_dlist(t_dlist *lst, int rev)
{
	t_dnode	*cur;
	t_dnode	*start;
	t_dnode *end;
	int		n;

	if (!lst)
		return ;
	start = rev ? lst->head : lst->tail;
	end = rev ? lst->tail : lst->head;
	cur = start;
	n = 0;
	printf("* %slist content, %ld elems (tail:%p head:%p):\n",
		   (rev ? "reverse " : ""),
		   lst->size,
		   lst->tail, lst->head);
	while (cur)
	{
		printf("\tnode[%d - %p]: %d (prev:%p next:%p)\n", n, cur,
			   cur->data ? *(int*)cur->data : -1, cur->prev, cur->next);
		if (cur == end)
			break ;
		cur = rev ? cur->prev : cur->next;
		n++;
	}
}

int		test_dlist_push(t_dlist *lst, unsigned n, int val)
{
	static int	var = 42;

	var = val;
	while (n--)
		ft_dlist_add_back(lst, ft_dnode_new(&var, sizeof(int), NF_DESTROY_NODE));
	print_dlist(lst, 0);
	return (0);
}

int		test_dlist_destroy(t_dlist *list, t_dnode **n, size_t times)
{
	if (!n)
		return (1);
	times = times > list->size ? list->size : times;
	while (times-- && *n)
	{
		printf("* destroying %p (%s)\n", *n, (*n && *n == list->tail && *n == list->head)
			   ? "last node"
			   : (*n == list->tail
				  ? "tail"
				  : (*n == list->head
					 ? "head"
					 : "node")));
		ft_dlist_remove(list, *n, ft_dlist_deleter);
	}
	print_dlist(list, 0);
	return (0);
}

int		test_dlist_add5(t_test *test)
{
	(void)test;
	static unsigned const	ndata = 5;
	static int const		vdata = 42;

	printf("* adding %u int(s) = %d\n", ndata, vdata);
	test_dlist_push(&g_list, ndata, vdata);
	return (!(g_list.size == ndata && g_list.tail && g_list.head));
}

int		test_dlist_deltail5(t_test *test)
{
	(void)test;
	static unsigned const	ndata = 5;

	printf("* removing %u node(s) at tail\n", ndata);
	test_dlist_destroy(&g_list, &g_list.tail, 5);
	if (g_list.size)
		return (error_test(test, 1, "invalid list size: %ld, should be: %u", g_list.size, (unsigned)0));
	if (g_list.head)
		return (error_test(test, 1, "head not null, should be null"));
	if (g_list.tail)
		return (error_test(test, 1, "tail not null, should be null"));
	return (0);
}

int		test_dlist_delhead5(t_test *test)
{
	(void)test;
	static unsigned const	ndata = 5;

	printf("* removing %u node(s) at head\n", ndata);
	test_dlist_destroy(&g_list, &g_list.head, 5);
	if (g_list.size)
		return (error_test(test, 1, "invalid list size: %ld, should be: %u", g_list.size, (unsigned)0));
	if (g_list.head)
		return (error_test(test, 1, "head not null, should be null"));
	if (g_list.tail)
		return (error_test(test, 1, "tail not null, should be null"));
	return (0);
}

int		test_dlist_clear(t_test *test)
{
	(void)test;
	printf("* removing all nodes.\n");
	ft_dlist_clear(&g_list, ft_dlist_deleter);
	if (g_list.size)
		return (error_test(test, 1, "invalid list size: %ld, should be: %u", g_list.size, (unsigned)0));
	if (g_list.head)
		return (error_test(test, 1, "head not null, should be null"));
	if (g_list.tail)
		return (error_test(test, 1, "tail not null, should be null"));
	return (0);
}

int		test_dlist_delrand5(t_test *test)
{
	(void)test;
	int		times = 5;
	t_dnode	*part;
	static unsigned const	ndata = 5;

	printf("* removing %u node(s) randomly\n", ndata);
	while (times--)
	{
		part = g_list.tail;
		if ((rand() % 100) > 50)
			part = g_list.head;
		test_dlist_destroy(&g_list, &g_list.head, 1);
	}
	if (g_list.size)
		return (error_test(test, 1, "invalid list size: %ld, should be: %u", g_list.size, (unsigned)0));
	if (g_list.head)
		return (error_test(test, 1, "head not null, should be null"));
	if (g_list.tail)
		return (error_test(test, 1, "tail not null, should be null"));
	return (0);
}

int		main(void)
{
	t_test	tests[DLIST_COUNT];
	int		code;

	srand(time(NULL));
	code = 0;
	printf("* initializing dlist\n");
	ft_dlist_init(&g_list);
	init_test(&tests[DLIST_ADD5], "add 5 at back", test_dlist_add5);
	init_test(&tests[DLIST_DELTAIL5], "delete 5 at tail", test_dlist_deltail5);
	init_test(&tests[DLIST_DELHEAD5], "delete 5 at head", test_dlist_delhead5);
	init_test(&tests[DLIST_CLEAR], "clear all", test_dlist_clear);
	init_test(&tests[DLIST_DELRAND5], "delete 5 randomly", test_dlist_delrand5);
	code += run_test(&tests[DLIST_ADD5]);
	code += run_test(&tests[DLIST_DELTAIL5]);
	code += run_test(&tests[DLIST_ADD5]);
	code += run_test(&tests[DLIST_DELHEAD5]);
	code += run_test(&tests[DLIST_ADD5]);
	code += run_test(&tests[DLIST_DELRAND5]);
	code += run_test(&tests[DLIST_ADD5]);
	code += run_test(&tests[DLIST_CLEAR]);
	ft_dlist_clear(&g_list, ft_dlist_deleter);
	return (code);
}
