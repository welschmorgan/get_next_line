/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 21:38:33 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/19 13:51:22 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void		ft_putstr_fd(char const *str, int fd)
{
	if (!str)
		write(fd, FT_INVALID_STR, ft_strlen(FT_INVALID_STR));
	write(fd, str, ft_strlen(str));
}
