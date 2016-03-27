/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 11:20:17 by mwelsch           #+#    #+#             */
/*   Updated: 2016/03/27 18:04:50 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

#define PUSH_BLOCK(LST, DATA) ft_dlist_push_back_str(LST, DATA, NF_DESTROY_ALL)

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
	fd->fd = fdi;
	fd->init = TRUE;
	fd->code = READ_OK;
	fd->count = 0;
	fd->stop = FALSE;
	ft_bzero(fd->buf, BUFF_SIZE);
	ft_dlist_init(&fd->block);
	ft_dlist_init(&fd->lines);
	return (fd);
}

int				ft_read_fd(t_fd *fd)
{
	char		*ptr;

	ft_bzero(fd->buf, BUFF_SIZE);
	fd->count = read(fd->fd, fd->buf, BUFF_SIZE);
	if (fd->count > 0)
		fd->code = READ_OK;
	else if (fd->count < 0)
		fd->code = READ_ERR;
	else
		fd->code = READ_EOF;
	if (fd->code == READ_ERR)
		return (fd->code);
	if (fd->code != READ_ERR)
	{
		ptr = fd->buf;
		while (ptr < (fd->buf + fd->count) && *ptr)
		{
			if (*ptr == '\n')
				ft_push_fd(fd);
			else
				PUSH_BLOCK(&fd->block, ft_strndup(ptr, 1));
			ptr++;
		}
	}
	return (fd->code);
}

/*
** == READ_OK
*/

int				ft_push_fd(t_fd *fd)
{
	t_dnode		*cur;
	char		*pdata;
	char		*buf;
	char		*pbuf;

	buf = ft_strnew(fd->block.size);
	pbuf = buf;
	cur = fd->block.tail;
	while (cur)
	{
		pdata = (char*)cur->data;
		if (pdata)
			*pbuf = *pdata;
		pbuf++;
		cur = cur->next;
	}
	*pbuf = '\0';
	ft_dlist_clear(&fd->block, ft_dlist_deleter);
	ft_dlist_push_back_str(&fd->lines, buf, NF_DESTROY_ALL);
	return (fd->code);
}

int				ft_process_fd(t_dlist *fds, t_fd *fd, char **line)
{
	t_dnode		*cur;

	if (fd->code == READ_ERR)
		return (fd->code);
	if (fd->block.tail)
		ft_push_fd(fd);
	*line = NULL;
	if (!fd->lines.tail)
	{
		fd->stop = TRUE;
		fd->code = READ_EOF;
		ft_dlist_clear(&fd->lines, ft_dlist_deleter);
		ft_dlist_clear(&fd->block, ft_dlist_deleter);
		cur = ft_dlist_find(fds, (void const *)fd);
		if (cur)
		{
			ft_bzero(cur->data, sizeof(t_fd));
			ft_dlist_remove(fds, &cur, ft_dlist_deleter);
		}
		return (READ_EOF);
	}
	fd->code = READ_OK;
	cur = fd->lines.tail;
	if (cur)
	{
		*line = cur->data;
		cur->data = NULL;
	}
	ft_dlist_remove(&fd->lines,
					&cur,
					ft_dlist_deleter);
	return (fd->code);
}

/*
** #if defined(SMART_GET_NEXT_LINE) && SMART_GET_NEXT_LINE == 1
**	if (*line)
**	  ft_strdel(line);
** #endif
**	cur = fd->lines.tail;
**	if (cur)
**	{
** #if defined(SMART_GET_NEXT_LINE) && SMART_GET_NEXT_LINE == 1
**		*line = ft_strdup((char*)cur->data);
** #endif
*/

int				get_next_line(int const fd, char **line)
{
	static t_dlist	fds;
	t_fd			*pfd;

	if (fd < 0 || !line)
		return (READ_ERR);
	pfd = ft_init_fd(&fds, fd);
	if (pfd->lines.tail)
		return (ft_process_fd(&fds, pfd, line));
	else if (pfd->stop)
		return (pfd->code);
	while (pfd->code > READ_EOF)
		ft_read_fd(pfd);
	return (ft_process_fd(&fds, pfd, line));
}

#undef PUSH_BLOCK
