#include "get_next_line.h"
#include <unistd.h>

t_fd			*ft_init_fd(t_fd *fd, int const fdi)
{
	if (!fd || fd->init)
		return (fd);
	fd->fd = fdi;
	fd->init = TRUE;
	fd->code = READ_OK;
	fd->count = 0;
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
	if (fd->code == READ_OK)
	{
		ptr = fd->buf;
		while (ptr < (fd->buf + fd->count) && *ptr)
		{
			if (*ptr == '\n')
				ft_push_fd(fd);
			else
				ft_dlist_push_back_str(&fd->block,
									   ft_strndup(ptr, 1),
									   NF_DESTROY_ALL);
			ptr++;
		}
	}
	return (fd->code);
}

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

int				ft_process_fd(t_fd *fd, char **line)
{
	t_dnode		*cur;

	if (fd->code == READ_ERR)
		return (fd->code);
	fd->code = READ_OK;
	if (*line)
		ft_strdel(line);
	cur = fd->lines.tail;
	if (cur)
		*line = ft_strdup((char*)cur->data);
	ft_dlist_remove(&fd->lines,
					&cur,
					ft_dlist_deleter);
	if (!fd->lines.tail)
	{
		ft_dlist_clear(&fd->lines, ft_dlist_deleter);
		ft_dlist_clear(&fd->block, ft_dlist_deleter);
		fd->code = READ_EOF;
	}
	return (fd->code);
}

int				get_next_line(int const fd, char **line)
{
	static t_fd	fds[FD_MAX];
	t_fd		*pfd;

	if (fd < 0 || fd >= FD_MAX)
		return (READ_ERR);
	pfd = &fds[fd];
	ft_init_fd(pfd, fd);
	if (pfd->lines.tail)
		return (ft_process_fd(pfd, line));
	while (pfd->code == READ_OK)
	{
		ft_read_fd(pfd);
		if (pfd->code != READ_OK)
			break ;
	}
	return (ft_process_fd(pfd, line));
}
