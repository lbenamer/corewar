#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
int main(void)
{

	int fd;
	char *line = NULL;
	fd = open("header_m42.txt", O_RDONLY);
	while(get_next_line(fd, &line) > 0)
	{
		ft_putendl(line);
		free(line);
		line = NULL;
	}
	while(1);
	return 0;
}