/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_extract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 12:50:46 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/28 13:12:41 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dnode				*ft_dlist_extract(t_dlist *list,
									t_dnode *node)
{
	if (!list || !node)
		return (node);
	if (list->tail == node || !list->tail)
		list->tail = node->next;
	if (list->head == node || !list->head)
		list->head = node->prev;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (list->size)
		list->size--;
	node->parent = NULL;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}





