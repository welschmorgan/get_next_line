/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_contains.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 12:46:05 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/28 12:46:25 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

int					ft_dlist_contains(t_dlist *list,
									t_dnode *node)
{
	t_dnode			*cur;

	if (!list)
		return (0);
	cur = list->tail;
	while (cur && cur != node)
		cur = cur->next;
	return (cur == node);
}
