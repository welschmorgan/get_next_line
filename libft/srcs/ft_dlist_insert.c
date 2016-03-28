/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 12:51:31 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/28 13:22:00 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_dnode				*ft_dlist_insert_first(t_dlist *list, t_dnode *node)
{
	if (list && node)
	{
		node->parent = list;
		node->next = NULL;
		node->prev = NULL;
		list->tail = node;
		list->head = list->tail;
		list->size = 1;
	}
	return (node);
}

t_dnode				*ft_dlist_insert_after(t_dlist *list, t_dnode *new_node,
										t_dnode *prev)
{
	t_dnode			*next;

	if (!new_node || !list)
		return (new_node);
	if (!list->tail)
		return (ft_dlist_insert_first(list, new_node));
	if (!prev)
		prev = list->head;
	next = prev->next;
	new_node->parent = list;
	new_node->prev = prev;
	new_node->next = next;
	prev->next = new_node;
	if (next)
		next->prev = new_node;
	if (prev == list->head)
		list->head = new_node;
	list->size++;
	return (new_node);
}

t_dnode				*ft_dlist_insert_before(t_dlist *list,
											t_dnode *new_node,
											t_dnode *next)
{
	t_dnode			*prev;

	if (!new_node || !list)
		return (new_node);
	if (!list->tail)
		return (ft_dlist_insert_first(list, new_node));
	if (!next)
		next = list->tail;
	prev = next->prev;
	new_node->parent = list;
	new_node->prev = prev;
	new_node->next = next;
	next->prev = new_node;
	if (prev)
		prev->next = new_node;
	if (next == list->tail)
		list->tail = new_node;
	list->size++;
	return (new_node);
}
