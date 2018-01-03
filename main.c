#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/*int	main(int argc, char **argv)
{
	int		fd;
	int		ret;
	char	*line;
	int		i;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (1);
		ret = 1;
		i = 0;
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			dprintf(1,"line renvoyer : %s\n",line );
			ft_strdel(&line);
		}
//		printf("tototo333333333332 \n");
	}
	if (argc == 1)
	{
		fd = 1;
		ret = 1;
		i = 0;
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			ft_putstr(line);
			ft_putstr("\n");
			ft_strdel(&line);
		}
	}
	return (0);
}*/


int		main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
	while (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		free(line);
	}
	if (argc == 2)
		close(fd);
}
