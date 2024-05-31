#include "../libft.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int	fd;
	char	*str;

	fd = open("test", O_RDONLY);
	while (str = get_next_line(fd))
	{
		printf("%s", str);
		free(str);
	}
	printf("%s", str);
}
