#include "libft.h"
#include <stdio.h>

static int char_to_int(char	hex_or_num)
{
	if (hex_or_num >= '0' && hex_or_num <='9')
		return (hex_or_num - '0');
	else
	{
		return (hex_or_num - 55);
	}
	return (0);
}

static int hex_hdler(char *hex_str)
{
	int	index;
	int	return_value;

	index = 0;
	return_value = 0;
	while (hex_str[index])
	{
		hex_str[index] = ft_toupper(hex_str[index]);
		return_value = char_to_int(hex_str[index]);
		return_value = 0;
		++index;
	}
	return (return_value);
}

int	ult_atoi(char *str)
{
	int	index;

	index = 0;
	if (str[index] == '0' && str[index + 1] == 'x')
	{
		hex_hdler(&(str[index + 2])); // get hex value to base 10
	}
	else
	{
		while (*str >= '0' && *str <= '9')
			++str;
	}
	return (0);
}

int	main(void)
{
	char	str[16] = "0xFaBCdE1234";
	int	num = 0x000010;
	printf("0x000010: %d\n", num);
	num = 0x000100;
	printf("0x000100: %d\n", num);
	num = 0x000200;
	printf("0x000200: %d\n", num);
	ult_atoi(str);
}
