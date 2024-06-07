#include "libft.h"
#include <stdio.h>

int	main(void)
{
	char	**str;
	int	i = 0;

	str = ft_split((void *)0, ' ');
	printf("%p", str);
	while (str[i] != 0)
	{
		printf ("%s", str[i]);
		i++;
	}
	printf("%s", str[i]);
}
