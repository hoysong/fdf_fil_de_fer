#include "libft.h"
#include <stdio.h>

int	main(void)
{
	char	**str;
	int	i = 0;
	str = ft_split("1 0 4  1 0\n", ' ');

	while (str[i] != 0)
	{
		printf ("%s", str[i]);
		i++;
	}
}
