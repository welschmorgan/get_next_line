/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_extract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 12:50:46 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/29 11:58:51 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_dnode				*ft_dlist_extract(t_dlist *list,
									t_dnode *node)
{
	if (!list || !node || !list->size)
		return (node);
	printf("* extract node %p - data:%p (prev:%p next:%p tail:%p head:%p)\n", node, node->data, node->prev, node->next, list->tail, list->head);
	if (list->tail == node && list->head != node)
	{
		list->tail = list->tail->next;
		if (list->tail)
			list->tail->prev = NULL;
	}
	else if (list->head == node && list->tail != node)
	{
		list->head = list->head->prev;
		if (list->head)
			list->head->next = NULL;
	}
	else if (list->head == node && list->tail == node)
		list->tail = list->head = NULL;
	else if (list->head != node && list->tail != node)
	{
		if (node->prev)
			node->prev->next = node->next;
		if (node->next)
			node->next->prev = node->prev;
	}
	if (list->size)
		list->size--;
	node->parent = NULL;
	node->prev = NULL;
	node->next = NULL;
	printf("\tdata:%p prev:%p next:%p tail:%p head:%p\n", node->data, node->prev, node->next, list->tail, list->head);
	return (node);
}







