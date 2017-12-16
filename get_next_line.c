#include "get_next_line.h"
#include "../libft/libft.h"
#include "stdlib.h"
#include <string.h>
#include <stdio.h>

char        **ft_realloc_2tab(char **str, const unsigned int size)
{
    char    **tmp;
    int     i;

    if (!size)
        str = (char **)malloc(sizeof(char *));
    else if (size >= 1)
    {
        i = 0;
        if(!(tmp = (char **)malloc(sizeof(char *) * size)))
            return (0);
        while (*str[i])
        {
            dprintf(1,"i=%d\n",i);
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

    if (fd < 0 || !line || BUFF_SIZE <= 0)
        return (-1);
    str = ft_realloc_2tab(str,(unsigned int)(fd - 3));
    return (1);
}
