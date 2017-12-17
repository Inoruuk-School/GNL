/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/17 04:15:35 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/17 06:16:56 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

static t_gnl			*ft_gnlnew(int fd, t_list *lst)
{
	t_gnl	*gnl;

	gnl->fd = fd;
	gnl->lst = ft_lstnew(lst->content, lst->content_size);
	return (gnl);
}

static t_list			*ft_fill_lst(int fd)
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

static char				*ft_seek_n_fill(t_list *gnl)
{
	char	*str;

	str = ft_memcpy(ft_memset(str, '\0', gnl->content_size), gnl->content);
	while (*str)
	{
		
	}
}

int						get_next_line(const int fd, char **line)
{
	static t_gnl		*gnl = NULL;
	t_gnl				*tmp;

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (!gnl) /*[1]creation premiere liste*/
		gnl = ft_gnlnew(fd, ft_fil_llst(fd));
	if (gnl->fd != fd) /*[2]recherche fd et si non trouver creation next liste*/
	{
		tmp = gnl->nextgnl? gnl->nextgnl: gnl;
		while (tmp->nextgnl && tmp->fd != fd)
			tmp = tmp->nextgnl;
		if (tmp->fd != fd && !tmp->nextgnl)
			{
				tmp->nextgnl = ft_gnlnew(fd, ft_fill_lst(fd));
				tmp = tmp->nextgnl;
			}
	}
	*line = ft_seek_n_fill(tmp->lst);
	return (1);
}
