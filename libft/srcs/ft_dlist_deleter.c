/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_deleter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 12:46:36 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/29 11:17:44 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_dlist_deleter(t_dnode *n)
{
	if (n->data && ((n->flag & NF_DESTROY_DATA) != 0))
		ft_memdel((void**)&n->data);
	n->data = NULL;
}
