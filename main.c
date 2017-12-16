#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int ac, char **av)
{
    int i;
    int fd;
    char **line;

    i = 0;
    if (ac >= 2)
        while (i++ <= ac)
        {
            fd = open(av[1], O_RDONLY);
            if (get_next_line(fd,line))
                printf("%d\n",1 );
        }
    return 0;
}
