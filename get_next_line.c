#include "get_next_line.h"
#include "stdlib.h"
#include <string.h>


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
        while (*str)
            tmp[i] = strcpy(tmp[i],str[i]);
            i++;
        free (str);
    }
    return (tmp);
}

int         get_next_line(const int fd, char **line)
{
    int                 i;
    static char         **str;

    i = 0;
    str = ft_realloc_2tab(str,(unsigned int)(fd - 3));

    return (1);
}
