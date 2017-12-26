/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/17 04:15:35 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/26 20:05:37 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static t_gnl			*ft_gnlnew(const int fd, t_list *lst)
{
	t_gnl	*gnl;

	gnl->fd = fd;
	gnl->lst = ft_lstnew(lst->content, lst->content_size);
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
		lst = ft_seek_n_fill(*tmp, buff, ret);
		while (lst->next)
			dprintf(1,"content :%s\n",tmp->content);
	}
	return (lst);
}

t_list			*ft_seek_n_fill(t_list **lst, char *buff, const int ret)
{
	t_list	*tmplst;
	char	*tmpbuff;
	char	*str;
	int 	size;

	tmplst = lst;
	if (tmplst->content != 0) /*Si content contien deja un bout de ligne*/
		if((tmpbuff = ft_strchr(buff, '\n')) != NULL && *buff)
		{
			dprintf(1,"seek_n_fill1.2\n");
			size = tmpbuff - buff;
			str = ft_strcat(tmplst->content,ft_strsub(buff, 0, size));
			tmplst = ft_lstnew(str, ft_strlen(str));
			buff = tmpbuff + 1;
			tmplst->next = ft_lstnew(0, 0);
			tmplst = tmplst->next;
		}
	while ((tmpbuff = ft_strchr(buff, '\n')) != NULL && *buff)
	{
		tmplst =ft_lstnew(ft_strsub(buff, 0, tmpbuff - buff), tmpbuff - buff);
		dprintf(1,"ft_seek_n_fill : %s\n",tmplst->content);
		buff = tmpbuff + 1;
//		dprintf(1,1,1,"buff :%s\ttmpbuff : %s\n",buff,tmpbuff + 1 );
		tmplst->next = ft_lstnew(0, 0);
		tmplst = tmplst->next;
	}
	if (*buff)/*Si buff contient encore des lettres mais qu'il n y q pas de \n*/
		{
			tmplst =ft_lstnew(ft_strsub(buff, 0, BUFF_SIZE), ft_strlen(buff));
//			dprintf(1,"content :%s\n",tmplst->content );
		}
//	dprintf(1,"lstcontent :%s\n",lst->content);
	return (lst);
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
	*line = ft_strdup(tmp->lst->content);
	return (1);
}
