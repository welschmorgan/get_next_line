/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 09:20:18 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/28 12:55:56 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "get_next_line.h"
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

void	print_dlist(t_dlist *lst)
{
	t_dnode	*cur;
	int		n;

	cur = lst->tail;
	n = 0;
	printf("* list content, %ld elems (tail:%p head:%p):\n", lst->size, lst->tail, lst->head);
	while (cur)
	{
		printf("\tnode[%d - %p]: %d (prev:%p next:%p)\n", n, cur, *(int*)cur->data, cur->prev, cur->next);
		cur = cur->next;
		n++;
	}

}
int		test_dlist()
{
	t_dlist	lst;
	int		var = 42;

	printf("* initializing dlist\n");
	ft_dlist_init(&lst);

	printf("* adding 3 int(s) = 42\n");
	ft_dlist_add_back(&lst, ft_dnode_new(&var, sizeof(int), NF_DESTROY_NODE));
	ft_dlist_add_back(&lst, ft_dnode_new(&var, sizeof(int), NF_DESTROY_NODE));
	ft_dlist_add_back(&lst, ft_dnode_new(&var, sizeof(int), NF_DESTROY_NODE));
	print_dlist(&lst);
	printf("* destroy tail\n");
	ft_dlist_remove(&lst, &lst.tail, ft_dlist_deleter);
	print_dlist(&lst);
	printf("* destroy head\n");
	ft_dlist_remove(&lst, &lst.head, ft_dlist_deleter);
	print_dlist(&lst);
	printf("* destroy head\n");
	ft_dlist_remove(&lst, &lst.tail, ft_dlist_deleter);
	print_dlist(&lst);

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
