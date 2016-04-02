/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 11:20:17 by mwelsch           #+#    #+#             */
/*   Updated: 2016/04/02 15:19:21 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>

t_fd			*ft_init_fd(t_dlist *fds, int const fdi)
{
	t_dnode		*cur;
	t_fd		*fd;

	fd = NULL;
	cur = fds->tail;
	while (cur)
	{
		if ((fd = (t_fd*)cur->data) && fd->fd == fdi)
			break ;
		cur = cur->next;
	}
	if (!fd)
	{
		ft_dlist_add_back(fds, (cur = ft_dnode_new(ft_memalloc(sizeof(t_fd)),
												   sizeof(t_fd),
												   NF_DESTROY_ALL)));
		fd = (t_fd*)cur->data;
		fd->init = FALSE;
	}
	if (fd->init)
		return (fd);
	fd->overflow = 0;
	fd->eof = 0;
	fd->fd = fdi;
	fd->init = TRUE;
	fd->code = READ_OK;
	fd->count = 0;
	ft_bzero(fd->buf, BUFF_SIZE);
	ft_dlist_init(&fd->lines);
	return (fd);
}

int				ft_read_fd(t_fd *fd)
{
	ft_bzero(fd->buf, BUFF_SIZE);
	fd->count = read(fd->fd, fd->buf, BUFF_SIZE);
	if (fd->count < 0)
		fd->code = READ_ERR;
	else if (!fd->count)
		fd->code = READ_EOF;
	else if (fd->count > 0)
		fd->code = READ_OK;
	return (fd->code);
}

int				ft_push_fd(t_fd *fd)
{
	char		*pend;
	char		*pstart;
	char		*pcur;
	char		*pdup;

	pstart = fd->buf;
	pend = fd->buf + fd->count;
	pcur = pstart;
	while ((pcur = ft_strchr(pstart, '\n')) && pcur < pend)
	{
		*pcur = 0;
		pdup = fd->overflow
			? ft_strjoin((char*)fd->lines.head->data, pstart)
			: ft_strdup(pstart);
		printf("[PUSH] %s.\n", pdup);
		if (fd->overflow)
		{
			ft_dlist_remove(&fd->lines, fd->lines.head, ft_dlist_deleter);
			fd->overflow = 0;
		}
		ft_dlist_add_back_str(&fd->lines, pdup, NF_DESTROY_ALL);
		pstart = pcur + 1;
	}
	if (pstart < pend)
	{
		pdup = fd->overflow
			? ft_strjoin((char*)fd->lines.head->data, pstart)
			: ft_strdup(pstart);
		printf("[PUSH] %s.\n", pdup);
		if (fd->overflow)
		{
			ft_dlist_remove(&fd->lines, fd->lines.head, ft_dlist_deleter);
			fd->overflow = 0;
		}
		ft_dlist_add_back_str(&fd->lines, pdup, NF_DESTROY_ALL);
	}
	ft_bzero(fd->buf, BUFF_SIZE);
	fd->overflow = (fd->count >= BUFF_SIZE);
	return (fd->code);
}

# define FD_OK(fd) (fd->code >= READ_OK)
# define FD_EOF(fd) (fd->code == READ_EOF)
# define FD_ERR(fd) (fd->code <= READ_ERR)

# define FD_NODE(fds, fd)	ft_dlist_find(fds, (void const *)fd)

# define FD_HAS_LINE(fd) (fd->lines.tail != NULL)
# define FD_CLEAR_LINES(fd) ft_dlist_clear(&fd->lines, ft_dlist_deleter)
# define FD_PROCESS(fds, fd, l) ft_process_fd(fds, fd, l)

int				ft_process_fd(t_dlist *fds, t_fd *fd, char **line)
{
	t_dnode		*cur;

	fd->code = READ_OK;
	if (fd->eof && !FD_HAS_LINE(fd))
	{
		fd->eof = 0;
		FD_CLEAR_LINES(fd);
		if ((cur = FD_NODE(fds, fd)))
			ft_dlist_remove(fds, cur, ft_dlist_deleter);
		*line = NULL;
		return (READ_EOF);
	}
	cur = fd->lines.tail;
	*line = cur->data;
	cur->data = NULL;
	ft_dlist_remove(&fd->lines, cur, ft_dlist_deleter);
	return (fd->code);
}

int				get_next_line(int const fd, char **line)
{
	static t_dlist	fds;
	t_fd			*pfd;
	int				code;

	if (fd < 0 || !line)
		return (READ_ERR);
	pfd = ft_init_fd(&fds, fd);
	if (!FD_HAS_LINE(pfd))
	{
		while (!pfd->eof)
		{
			while ((code = ft_read_fd(pfd)) == READ_OK)
				ft_push_fd(pfd);
			if (code == READ_EOF)
				pfd->eof = 1;
		}
	}
	return (FD_PROCESS(&fds, pfd, line));
}

#undef PUSH_BLOCK
