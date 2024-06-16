/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:25:34 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/13 17:48:10 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"

static void	to_upper(char *char_ptr)
{
	if (*char_ptr <= 'z' && *char_ptr >= 'a')
		*char_ptr -= 32;
}

static int init(char *num_str)
{
	static char *hold;
	
	if (hold == 0)
	{
		return (0);
	}
	else
	{
		hold = num_str;
	}
}

int mini_atoi(char **num_str)
{
	int	int_value;

	int_value = 0;
	while (**num_str)
	{
//		int_value = (int_value * 10) 
		(*num_str)++;
	}
}

int	hex_to_dec(char *num_str, int ***int_arr)
{
	int	int_value;

	int_value = init(num_str);

	int_value = 0;
	if (*num_str == '0' && *(num_str + 1) == 'x')
		num_str = num_str + 2;
	while (*num_str)
	{
		if ('0' <= *num_str && *num_str <= '9')
			int_value = (int_value * 16) + (*num_str - '0');
		if ('A' <= *num_str && *num_str <= 'F')
			int_value = (int_value * 16) + (*num_str - 55);
		++num_str;
	}
	return (int_value);
}

//int	hex_to_dec(char *num_str, int ***int_arr)
//{
//	int	int_value;
//
//	int_value = init(num_str);
//
//	int_value = 0;
//	if (*num_str == '0' && *(num_str + 1) == 'x')
//		num_str = num_str + 2;
//	while (*num_str)
//	{
//		if ('0' <= *num_str && *num_str <= '9')
//			int_value = (int_value * 16) + (*num_str - '0');
//		if ('A' <= *num_str && *num_str <= 'F')
//			int_value = (int_value * 16) + (*num_str - 55);
//		++num_str;
//	}
//	return (int_value);
//}
