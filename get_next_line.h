#ifndef GET_LINE_HH
# define GET_LINE_HH

# include <stddef.h>
# include <libft.h>

# define BUFF_SIZE		5
# define FD_MAX			255

# define READ_OK		1
# define READ_EOF		0
# define READ_ERR		-1

typedef struct	s_fd
{
	int			fd;
	int			init;
	int			code;
	int			count;
	char		buf[BUFF_SIZE];
	t_dlist		block;
	t_dlist		lines;
}				t_fd;

int				ft_push_fd(t_fd *fd);
int				ft_process_fd(t_fd *fd, char **line);
int				ft_read_fd(t_fd *fd);
t_fd			*ft_reset_fd(t_fd *fd);
t_fd			*ft_init_fd(t_fd *fd, int const fdi);

int				get_next_line(int const fd, char **line);

#endif
