#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int
	main(void)
{
	int		r;
	int		i = 0;
	char	*line;

	while (i < 10)
	{
		get_next_line(&line);
		printf("%s\n", line);
		free(line);
		i++;
	}
}
