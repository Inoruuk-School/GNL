/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/17 04:15:35 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/27 15:33:34 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static t_gnl			*ft_gnlnew(int fd, t_list *lst)
{
	t_gnl	*gnl;

	gnl->fd = fd;
	dprintf(1,"\tgnlfd :%d\n",gnl->fd);
	gnl->lst = lst;
	while (gnl->lst)
	{
		dprintf(1,"\tgnllstcontent :%s\n",gnl->lst->content);
		gnl->lst = gnl->lst->next;
	}
	return (gnl);
}

static t_list			*ft_fill_lst(const int fd)
{
	int		ret;
	char	buff[BUFF_SIZE + 1];
	t_list	*lst;
	t_list	*tmp;
	int i=0;

	lst = ft_lstnew(0, 0);
	tmp = lst;
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		lst = ft_seek_n_fill(&lst, buff, ret);
//		dprintf(1,"\tlstcontent :%s\n",lst->content);
	}
	return (tmp);
}

t_list			*ft_seek_n_fill(t_list **lst, char *buff, const int ret)
{
	char	*tmpbuff;
	char	*str;
	int 	size;

	if ((*lst)->content != 0) /*Si content contien deja un bout de ligne*/
		if((tmpbuff = ft_strchr(buff, '\n')) != NULL && *buff)
		{
			size = tmpbuff - buff;
			str = ft_strcat((*lst)->content,ft_strsub(buff, 0, size));
			*lst = ft_lstnew(str, ft_strlen(str));
			buff = tmpbuff + 1;
			(*lst)->next = ft_lstnew(0, 0);
			*lst = (*lst)->next;
		}
	while ((tmpbuff = ft_strchr(buff, '\n')) != NULL && *buff)
	{
		size = tmpbuff - buff;
//		dprintf(1,"ft_seek_n_fill : %s\n",(*lst)->content);
		(*lst)->next = ft_lstnew(ft_strsub(buff, 0, size), size);
		buff = tmpbuff + 1;
		*lst = (*lst)->next;
	}
	if (*buff)/*Si buff contient encore des lettres mais qu'il n y a pas de \n*/
		*lst =ft_lstnew(ft_strsub(buff, 0, ret), ft_strlen(buff));
//	dprintf(1,"lstcontent :%s\n",(*lst)->content);
	return (*lst);
}

int						get_next_line(const int fd, char **line)
{
	static t_gnl		*gnl = NULL;
	t_gnl				*tmp;
	char buff[BUFF_SIZE + 1];
	int ret;

	if (fd < 0 || !line || BUFF_SIZE <= 0 || read(fd, buff, 0) == -1)
		return (-1);
	if (!gnl) /*[1]creation premiere liste*/
		gnl = ft_gnlnew(fd, ft_fill_lst(fd));
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
	dprintf(1,"%d\n",gnl->fd);
	*line = ft_strdup(tmp->lst->content);
	return (1);
}
