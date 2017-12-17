#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	char *line1;
	char *line2;
	char *line3;
	int fd1;
	int fd2;
	int fd3;
	int ret1;
	int ret2;
	int ret3;

	argc = 1 + 2;
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	fd3 = open(argv[3], O_RDONLY);

	ret1 = get_next_line(fd1, &line1);
	printf("Lecture1: %s\n", line1);
	free(line1);
	ret2 = get_next_line(fd2, &line2);
	printf("Lecture2: %s\n", line2);
	free(line2);
	ret3 = get_next_line(fd3, &line3);
	printf("Lecture3: %s\n", line3);
	free(line3);
	ret1 = get_next_line(fd1, &line1);
	printf("Lecture1: %s\n", line1);
	free(line1);
	ret2 = get_next_line(fd2, &line2);
	printf("Lecture2: %s\n", line2);
	free(line2);
	ret1 = get_next_line(fd1, &line1);
	printf("Lecture1: %s\n", line1);
	free(line1);
	ret2 = get_next_line(fd2, &line2);
	printf("Lecture2: %s\n", line2);
	free(line2);
	ret1 = get_next_line(fd1, &line1);
	printf("Lecture1: %s\n", line1);
	free(line1);
	ret2 = get_next_line(fd2, &line2);
	printf("Lecture2: %s\n", line2);
	free(line2);
	ret1 = get_next_line(fd1, &line1);
	printf("Lecture1: %s\n", line1);
	free(line1);
	ret1 = get_next_line(fd1, &line1);
	printf("Lecture1: %s\n", line1);
	free(line1);
	return (1);
}
