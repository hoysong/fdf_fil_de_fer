/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 19:21:21 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/13 16:02:26 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"

int	fdf_atoi(char **nptr)
{
	int	intnum;
	int	minus;

	intnum = 0;
	minus = 1;
	while ((*(*nptr) >= 9 && *(*nptr) <= 13) || *(*nptr) == ' ')
		(*nptr)++;
	if (*(*nptr) == '-')
	{
		minus = -1;
		(*nptr)++;
	}
	else if (*(*nptr) == '+')
		nptr++;
	while (*(*nptr) && *(*nptr) >= '0' && *(*nptr) <= '9')
		intnum = intnum * 10 + *(char *)nptr++ - '0';
	intnum *= minus;
	if (*(*nptr) == ',')
		(*nptr)++;
	return (intnum);
}
