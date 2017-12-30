#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 10
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include "../libft/libft.h"
#include "stdlib.h"

typedef struct	s_gnl
{
	int					fd;
	char				*str;
	struct s_gnl		*next;
}				t_gnl;

int 	        get_next_line(const int fd, char **line);

#endif
