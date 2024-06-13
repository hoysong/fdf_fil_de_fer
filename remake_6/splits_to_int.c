/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits_to_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:03:43 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/13 14:24:30 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

int	***splits_to_int(char ***splits, int file_line_count)
{
	int	thr_dim;
	int	sec_dim;
	int	***pased_data;
	static char	hold;

	gen_int_arr(count_x_elements((*splits)), file_line_count);

	thr_dim = 0;
	sec_dim = 0;
	while (splits[thr_dim] != NULL)
	{
		while (splits[thr_dim][sec_dim] != NULL)
		{
		}

	}
//	fdf_atoi(splits);
//0. int *** 배열 생성(int***)
//1. splits_to_int 에 splits 넘겨주기
//2. atoi에 넘겨주기
//2.1 atoi 에서는 기본적으로 z 값을 트리플 포인터의 0번 인덱스에 넣기.
//2.2 atoi 에서는 color값을 1번째 인덱스에 넣기.
	return (0);
}
