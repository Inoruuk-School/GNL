#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE
# define BUFF_SIZE 32
# include <unistd.h>

int         get_next_line(const int fd, char **line);

#endif
