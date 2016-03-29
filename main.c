/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 09:20:18 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/29 12:00:07 by mwelsch          ###   ########.fr       */
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
	int		n;

	if (!lst)
		return ;
	cur = rev ? lst->head : lst->tail;
	n = rev ? lst->size : 0;
	printf("* %slist content, %ld elems (tail:%p head:%p):\n",
		   (rev ? "reverse " : ""),
		   lst->size,
		   lst->tail, lst->head);
	while (cur)
	{
		printf("\tnode[%d - %p]: %d (prev:%p next:%p)\n", n, cur,
			   cur->data ? *(int*)cur->data : -1, cur->prev, cur->next);
		if (cur == (rev ? lst->tail : lst->head))
			break ;
		cur = rev ? cur->prev : cur->next;
		n = rev ? (n ? (n - 1) : 0) : (n + 1);
	}

}

int		test_dlist_push(t_dlist *lst, unsigned n, int val)
{
	static int	var = 42;

	printf("* adding 3 int(s) = %d\n", val);
	while (n--)
		ft_dlist_add_back(lst, ft_dnode_new(&var, sizeof(int), NF_DESTROY_NODE));
	print_dlist(lst, 0);
	return (0);
}

int		test_dlist_destroy(t_dlist *list, t_dnode **n)
{
	if (!(n && *n))
		return (1);
	printf("* destroying %p (%s)\n", *n, *n == list->tail ? "tail" : (*n == list->head ? "head" : "node"));
	ft_dlist_remove(list, n, ft_dlist_deleter);
	print_dlist(list, 0);
	return (0);
}

int		test_dlist()
{
	t_dlist	lst;

	printf("* initializing dlist\n");
	ft_dlist_init(&lst);
	test_dlist_push(&lst, 4, 42);
	test_dlist_destroy(&lst, &lst.tail);
	test_dlist_destroy(&lst, &lst.head);
	test_dlist_destroy(&lst, &lst.tail);
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
