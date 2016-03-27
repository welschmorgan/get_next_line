/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 11:20:07 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/27 16:30:49 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <libft.h>

# define BUFF_SIZE		50
# define FD_MAX			255

# define SHOW_LAST_LINE	1

# define READ_OK		1
# define READ_EOF		0
# define READ_ERR		-1

typedef struct	s_fd
{
	int			fd;
	int			init;
	int			code;
	int			stop;
	int			count;
	char		buf[BUFF_SIZE];
	t_dlist		block;
	t_dlist		lines;
}				t_fd;

t_fd			*ft_init_fd(t_dlist *fds, int const fdi);
int				ft_push_fd(t_fd *fd);
int				ft_process_fd(t_dlist *fds, t_fd *fd, char **line);
int				ft_read_fd(t_fd *fd);
int				get_next_line(int const fd, char **line);

#endif
