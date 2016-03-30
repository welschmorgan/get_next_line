/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 12:17:40 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/30 12:17:59 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		MAIN_H
# define	MAIN_H

# include <libft.h>

int		test_dlist();
void	print_dlist(t_dlist *lst, int rev);
int		test_dlist_push(t_dlist *lst, unsigned n, int val);
int		test_dlist_destroy(t_dlist *list, t_dnode **n, size_t times);

#endif
