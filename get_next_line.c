/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/17 04:15:35 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2018/01/14 19:58:35 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
static t_list			*ft_mod(t_list *lst, char *str)
{
	t_list	*lsttmp;

	str = ft_strcat((char *)lst->content, str);
	lsttmp = ft_lstnew(str, ft_strlen(str));
	free(lst->content);
	lst->content = NULL;
	lst->content_size = 0;
	free (lst);
//	lst = ft_lstnew(str, ft_strlen(str));
	return (lsttmp);
}

static void 			ft_del(void *content, size_t c_size)
{
	free(content);
	content = NULL;
	c_size = 0;
}

static t_gnl			*ft_gnlnew(int fd, t_list *lst)
{
	t_gnl	*gnl;

	if(!(gnl = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	gnl->fd = fd;
	gnl->lst = lst;
	return (gnl);
}

static t_list			*ft_fill_lst(const int fd)
{
	int		ret;
	char	buff[BUFF_SIZE + 1];
	t_list	*lst;
	t_list	*tmp;
	t_list	*head;

	lst = ft_lstnew(0,0);
	head = lst;
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
	//	if (*buff == '\n' && lst->next)
	//		lst = ft_seek_n_fill(&lst->next, buff + 1, ret, 0);
	//	else
			lst = ft_seek_n_fill(&lst, buff, ret, 0);
	}
	tmp = head->next;
	free(head);
	head = tmp;
	lst = head;
	return (head);
}

t_list			*ft_seek_n_fill(t_list **lst, char *buff, int ret, int size)
{
	char	*tmpbuff;
	char	*str;

	while (*buff == '\n')
		buff++;
	size = (tmpbuff = ft_strchr(buff, '\n')) ? tmpbuff - buff : 0;
	while (size)
	{
		if((*lst) && (*lst)->next && (str = ft_strsub(buff, 0, size)))
		{
//			str = ft_strcat((char *)(*lst)->next->content, str);
//			free((*lst)->next);
//			ft_lstdelone(&(*lst)->next,ft_del);
//			(*lst)->next = ft_lstnew(str, ft_strlen(str));
			(*lst)->next = ft_mod((*lst)->next, str);
			*lst = (*lst)->next;
		}
		else if (((*lst)->next = ft_lstnew(ft_strsub(buff, 0, size), size)))
			*lst = (*lst)->next;
		buff += size + 1;
		while(*buff == '\n')
			buff++;
		size = (tmpbuff = ft_strchr(buff, '\n')) ? tmpbuff - buff : 0;
	}
	if (*buff && !size)
	{
		if ((*lst)->next/* && (str = ft_strsub(buff, 0, ret))*/)
//		{
//			str = ft_strcat((char *)(*lst)->next->content, str);
//			free((*lst)->next);
//			ft_lstdelone(&(*lst)->next, ft_del);
//			(*lst)->next = ft_lstnew(str, ft_strlen(str));
			(*lst)->next = ft_mod((*lst)->next, /*str*/buff);
//		}
		else if (!(*lst)->next)
			(*lst)->next = ft_lstnew(ft_strsub(buff, 0, ret), ft_strlen(buff));
	}
	return (*lst);
}

int						get_next_line(const int fd, char **line)
{
	static t_gnl		*head = NULL;
	t_gnl				*tmp;
	t_list				*lsttmp;
	char 				buff[BUFF_SIZE + 1];

	if (fd < 0 || !line || BUFF_SIZE <= 0 || read(fd, buff, 0) == -1)
		return (-1);
	if (!head) /*[1]creation premiere liste*/
		head = ft_gnlnew(fd, ft_fill_lst(fd));
	if ((tmp = head) && tmp->fd != fd) /*[2]recherche fd et si non trouver creation next liste*/
	{
		while (tmp->nextgnl && tmp->fd != fd)
			tmp = tmp->nextgnl;
		if (tmp->fd != fd && !tmp->nextgnl)
		{
			tmp->nextgnl = ft_gnlnew(fd, ft_fill_lst(fd));
			tmp = tmp->nextgnl;
		}
	}
	if (tmp->lst && (*line = ft_strdup(tmp->lst->content)))
	{
		*(*line + tmp->lst->content_size) = '\0';
		lsttmp = tmp->lst->next;
		free(tmp->lst);
//		ft_lstdelone(&tmp->lst, ft_del);
		tmp->lst = lsttmp;
		return (1);
	}
	return (0);
}
