/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/17 04:15:35 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/30 18:23:25 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
		if (*buff == '\n' && lst->next)
			lst = ft_seek_n_fill(&lst->next, buff + 1, ret);
		else
			lst = ft_seek_n_fill(&lst, buff, ret);
	}
	lst = head;
	while (lst)
	{
		dprintf(1,"ligne: %s\n",lst->content);
		lst = lst->next;
	}
	return (head);
}

t_list			*ft_seek_n_fill(t_list **lst, char *buff, const int ret)
{
	char	*tmpbuff;
	char	*str;
	int 	size;

	size = (tmpbuff = ft_strchr(buff, '\n')) ? tmpbuff - buff : 0;
	while (size)
	{
		if((*lst) && (*lst)->next && (str = ft_strsub(buff, 0, size)))
		{
			str = ft_strcat((char *)(*lst)->next->content, str);
//			free(lst->next->content);
			(*lst)->next = ft_lstnew(str, ft_strlen(str));
			*lst = (*lst)->next;
		}
		else if (((*lst)->next = ft_lstnew(ft_strsub(buff, 0, size), size)))
			*lst = (*lst)->next;
		buff += size + 1;
		size = (tmpbuff = ft_strchr(buff, '\n')) ? tmpbuff - buff : 0;
	}
	if (*buff && !size)
	{
		while (*buff == '\n')
			buff++;
		if ((*lst)->next && (str = ft_strsub(buff, 0, ret)))
		{
			str = ft_strcat((char *)(*lst)->next->content, str);
//			free(lst->next->content);
			(*lst)->next = ft_lstnew(str, ft_strlen(str));
		}
		else
			(*lst)->next = ft_lstnew(ft_strsub(buff, 0, ret), ft_strlen(buff));
	}




//	if ((*lst)->next) /*cas ou il y a du reste de buff*/
//	{
//		if(size && ((*lst) = (*lst)->next) && (str = ft_strsub(buff, 0, size)))
//			{/*je rentre dans le reste pour le modifier*/
//				str = ft_strcat((char *)(*lst)->content, str);
//				*lst = ft_lstnew(str, ft_strlen(str));
//				buff += 1 + size;
//			}/*le reste est maintenant une ligne complete*/
//		else if (!size && ((*lst = (*lst)->next)))
//			{/*si !size alors il n y a pas de \n donc la ligne n est pas terminer*/
//				str = ft_strcat((char *)(*lst)->content, buff);
//				*lst = ft_lstnew(str, ft_strlen(str));
//			}/*alors je rentre buff dans lst->content*/
//	}
//	while (size)
//	{
//		(*lst)->next = ft_lstnew(buff, ret);
//		*lst = (*lst)->next;
//		size = (tmpbuff = ft_strchr(buff, '\n')) ? tmpbuff - buff : 0;
//		buff += 1 + size;
//	}






//	else if (size)/* pas de reste donc creer lst->next et remplir*/
/*		{
			(*lst)->next = ft_lstnew(buff, ret);
		}*/
/*
	if ((*lst)->content != 0)
	if((tmpbuff = ft_strchr(buff, '\n')) != NULL && *buff)
		{
			size = tmpbuff - buff;
			str = ft_strcat((*lst)->content, ft_strsub(buff, 0, size));
			*lst = ft_lstnew(str, ft_strlen(str));
			buff = tmpbuff + 1;
		}
	while ((tmpbuff = ft_strchr(buff, '\n')) != NULL && *buff)
	{
		size = tmpbuff - buff;
		if ((*lst)->content)
			{
				str = ft_strcat((*lst)->content, ft_strsub(buff, 0, size));
				*lst = ft_lstnew(str, ft_strlen(str));
			}
		else
			(*lst)->next = ft_lstnew(ft_strsub(buff, 0, size), size);
		buff = tmpbuff + 1;
		*lst = (*lst)->next ? (*lst)->next : *lst;
	}
	if (*buff && (*lst)->content)
	{
		size = ft_strlen(buff) + (*lst)->content_size;
		(*lst) = ft_lstnew(ft_strcat((*lst)->content, buff), size);
	}
	else if (*buff)
		(*lst)->next =ft_lstnew(ft_strsub(buff, 0, ret), ft_strlen(buff));
*/	return (*lst);
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
		while (tmp->nextgnl && tmp->fd != fd)
			tmp = tmp->nextgnl;
		if (tmp->fd != fd && !tmp->nextgnl)
		{
			tmp->nextgnl = ft_gnlnew(fd, ft_fill_lst(fd));
			tmp = tmp->nextgnl;
		}
	}
	*line = tmp->lst->content;
	return (1);
}
