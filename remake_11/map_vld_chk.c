/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_vld_chk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:15:46 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/29 01:43:09 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

// count unitl splits_one_line is not NULL
// and go back 1 byte to check it is newlin
int	count_x_elements(char **splits_one_line)
{
	int	elements;

	elements = 0;
	while (*splits_one_line != NULL)
	{
		++elements;
		++splits_one_line;
	}
	return (elements);
}

static void	setup(int *second_index, int *x_elements, char ****free_splits, char ***splits)
{
	*second_index = 0;
	*free_splits = splits;
	*x_elements = count_x_elements((*splits));
}

int	map_vld_chk(char ***splits)
{
	char	***free_splits;
	int		second_index;
	int		x_elements;
	int		map_chk_flg;

	setup(&second_index, &x_elements, &free_splits,splits);
	map_chk_flg = 1;
	while ((*splits) != NULL)
	{
		while ((*splits)[second_index] != NULL)
		{
			free((*splits)[second_index]);
			++second_index;
		}
		free((*splits));
		++splits;
		if ((second_index != x_elements))
		{
			map_chk_flg = 0;
		}
		second_index = 0;
	}
	free(free_splits);
	return (map_chk_flg);
}
