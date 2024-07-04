/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:25:34 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/04 18:41:53 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"

static void	to_upper(char *char_ptr)
{
	if (*char_ptr <= 'z' && *char_ptr >= 'a')
		*char_ptr -= 32;
}

void	hex_to_dec(char *num_str, int *height, int *color)
{
	int	int_value;

	int_value = 0;
	while (*num_str && *num_str != ',' && *num_str != '\n')
	{
		int_value = (int_value * 10) + (*num_str - '0');
		num_str++;
	}
	*height = int_value;
	int_value = 0;
	if (*num_str == ',')
		num_str++;
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
	if (int_value == 0)
		*color = 0xFFFFFF;
	else
		*color = int_value;
	return ;
}
