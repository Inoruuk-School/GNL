/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/17 04:15:35 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/29 19:54:48 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft/libft.h"
#include "stdlib.h"

static char			*ft_the_line(int fd, t_gnl *gnl)
{
	char	*str;
	char 	*buff;
	char 	*tmp;
	int 	ret;

	str = ft_strnew(0);
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		if ((tmp = ft_strchr(buff, '\n')))
			{
				str = ft_strcat(str, ft_strsub(buff, 0 ,tmp - buff);
			}
	}
	return (str);
}

static t_gnl	ft_gnlnew(int fd, char *str)
{
	t_gnl	*gnl;

	if (!(gnl = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	gnl->fd = fd;
	gnl->str = str;
	return (gnl);
}

int				get_next_line(const int fd, char **line)
{
    static t_gnl        *gnl = NULL;
    char                *tmp;
    char                *buff;
    int                 ret;

	if (fd < 0 || !line || BUFF_SIZE <= 0 || read(fd, buff, 0) == -1)
 		return (-1);
 	if (!gnl) /*[1]creation premiere liste*/
 		gnl = ft_gnlnew(fd, ft_fill_lst(fd));
    if ((ret = read(fd, buff, BUFF_SIZE) == BUFF_SIZE))
    {

    }
    return (1);
}
