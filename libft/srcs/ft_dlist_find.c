/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_find.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/27 13:57:16 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/27 13:58:28 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dnode		*ft_dlist_find(t_dlist *lst, void const *data)
{
	t_dnode	*cur;

	cur = lst->tail;
	while (cur)
	{
		if (((void const *)cur->data) == data)
			break ;
		cur = cur->next;
	}
	return (cur);
}









