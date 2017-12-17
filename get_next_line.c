/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: asiaux <asiaux@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/17 04:15:35 by asiaux       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/17 04:17:12 by asiaux      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft/libft.h"
#include "stdlib.h"


static char        **ft_alloc_n_realloc(char **str, const unsigned int size)
{
    char    **tmp;
    int     i;

    if (!size)
    {
        str = (char **)malloc(sizeof(char *));
        *str = ft_strnew(BUFF_SIZE);
    }
    else if (size >= 1)
    {
        i = 0;
        if(!(tmp = (char **)malloc(sizeof(char *) * size)))
            return (0);
        while (str[i])
        {
            tmp[i] = ft_strcpy(tmp[i], str[i]);
            i++;
        }
        free (str);
    }
    return (tmp);
}

int         get_next_line(const int fd, char **line)
{
    static char         **str;
    char                *tmp;
    char                *buff;
    int                 ret;

   if (fd < 0 || !line || BUFF_SIZE <= 0)
        return (-1);
    if (!*(line + fd - 3))
        str = ft_alloc_n_realloc(str,(unsigned int)(fd - 3));
    if ((ret = read(fd, buff, BUFF_SIZE) == BUFF_SIZE))
    {
        tmp = ft_strchr(buff, '\n');
        if (*tmp)
            {
                *(line + fd - 3) = ft_strncpy(*(line + fd - 3), buff, &tmp - &*(line + fd - 3));
            }
    }
    return (1);
}
