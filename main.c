/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 09:20:18 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/29 13:38:50 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "get_next_line.h"
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

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

	printf("* adding %u int(s) = %d\n", n, val);
	while (n--)
		ft_dlist_add_back(lst, ft_dnode_new(&var, sizeof(int), NF_DESTROY_NODE));
	print_dlist(lst, 0);
	return (0);
}

int		test_dlist_destroy(t_dlist *list, t_dnode *n, size_t times)
{
	if (!n)
		return (1);
	times = times > list->size ? list->size : times;
	while (times--)
	{
		printf("* destroying %p (%s)\n", n, (n && n == list->tail && n == list->head)
			   ? "last node"
			   : (n == list->tail
				  ? "tail"
				  : (n == list->head
					 ? "head"
					 : "node")));
		ft_dlist_remove(list, n, ft_dlist_deleter);
	}
	print_dlist(list, 0);
	return (0);
}

int		test_dlist()
{
	t_dlist	lst;

	printf("* initializing dlist\n");
	ft_dlist_init(&lst);
	test_dlist_push(&lst, 4, 42);

	test_dlist_destroy(&lst, lst.tail, 4);
	test_dlist_push(&lst, 4, 42);

	test_dlist_destroy(&lst, lst.head, 4);
	test_dlist_push(&lst, 3, 42);

	test_dlist_destroy(&lst, lst.head, 1);
	test_dlist_destroy(&lst, lst.tail, 1);
	test_dlist_destroy(&lst, lst.head, 1);
	print_dlist(&lst, 0);

	ft_dlist_clear(&lst, ft_dlist_deleter);
	return (0);
}
int		main(int argc, char *argv[])
{
	int	code;
	int	line;
	int	fd;
	char	*buf;

	test_dlist();
	sleep(10);
	fd = open(argc == 2 ? argv[1] : "/dev/stdin", O_RDONLY);
	if (fd < 0)
		return (fd);
	line = 0;
	while ((code = get_next_line(fd, &buf)) > 0)
	{
		printf("line#%u[%d]: \"%s\" (%u chars)\n", line, code, buf, (unsigned)strlen(buf));
		line++;
	}
	close(fd);
	return (0);
}
