/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits_to_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:03:43 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/13 17:55:02 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

int	***splits_to_int(char ***splits, int file_line_count)
{
	int	thr_dim;
	int	sec_dim;
	int	***parsed_data;
	static char	hold;

	parsed_data = gen_int_arr(count_x_elements((*splits)), file_line_count);

	thr_dim = 0;
	sec_dim = 0;
	while (splits[thr_dim] != NULL)
	{
		while (splits[thr_dim][sec_dim] != NULL)
		{
			hex_to_dec(splits[thr_dim][sec_dim], &(parsed_data[0][thr_dim][sec_dim]), &(parsed_data[1][thr_dim][sec_dim]));
			++sec_dim;
		}
		++thr_dim;
		sec_dim = 0;
	}
	/* parsed_data check */
	printf("#############parsed_data check!#############\n");
	thr_dim = 0;
	sec_dim = 0;
	int one_dim = 0;
	while (thr_dim < 2)
	{
		while(parsed_data[thr_dim][sec_dim])
		{
			while(one_dim < count_x_elements(*splits))
			{
				printf("%2d ",parsed_data[thr_dim][sec_dim][one_dim]);
				one_dim++;
			}
			printf("\n");
			one_dim = 0;
			sec_dim++;
		}
		sec_dim = 0;
		thr_dim++;
		printf("\n");
		printf("color value\n");
	}
	/* =====chk end===== */
	return (parsed_data);
}
