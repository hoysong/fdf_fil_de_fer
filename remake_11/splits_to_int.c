/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits_to_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:03:43 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/20 18:37:28 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

int	***splits_to_int(char ***splits, int x_elements, int file_line_count)
{
	int	thr_dim;
	int	sec_dim;
	int	***parsed_data;
	static char	hold;

	parsed_data = gen_int_arr(x_elements, file_line_count);

	thr_dim = 0;
	sec_dim = 0;
	while (splits[thr_dim] != NULL)
	{
		while (splits[thr_dim][sec_dim] != NULL)
		{
			hex_to_dec(
					splits[thr_dim][sec_dim],
					&(parsed_data[0][thr_dim][sec_dim]),
					&(parsed_data[1][thr_dim][sec_dim]));
			++sec_dim;
		}
		++thr_dim;
		sec_dim = 0;
	}
	return (parsed_data);
}
