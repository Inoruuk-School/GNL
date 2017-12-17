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
    dprintf(1, "ac=%d\n",ac);
        while (++i < ac)
        {
            fd = open(av[i], O_RDONLY);
            dprintf(1,"fd=%d\n",fd );
            if (get_next_line(fd,line) == 1)
                dprintf(1,"get next line a \"reussi\" %d\n",i);
        }
    return 0;
}
