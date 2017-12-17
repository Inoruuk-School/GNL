/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/17 04:15:35 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/17 05:22:12 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl			*ft_gnlnew(int fd, t_list *lst)
{
	t_gnl	*gnl;

	gnl->fd = fd;
	gnl->lst = ft_lstnew(lst->content, lst->content_size);
	return (gnl);
}

t_list			*ft_filllst(int fd)
{
	int		ret;
	char	*buff;
	t_list	*lst;
	t_list	*tmp;

	if ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		lst = ft_lstnew(buff, ret);
		tmp = lst;
		while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
			tmp->next = ft_lstnew(buff, ret);
	}
	return (lst);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl		*gnl;
	t_list				*lst;
	char				*buff;
	int					ret;

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (!gnl)
		gnl = ft_gnlnew(fd, ft_filllst(fd));
	if (gnl->fd != fd)
		gnl->nextgnl = ft_gnlnew(fd, ft_filllst(fd));
	return (1);
}
