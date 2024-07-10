/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pars_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 01:16:38 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/03 07:30:25 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"

void	free_parse_data(int ***data, int elements, int lines)
{
	int	thrd;
	int	scnd;
	int	frst;

	thrd = 0;
	frst = 0;
	scnd = 0;
	while (thrd < 3)
	{
		while (scnd < lines)
		{
			free(data[thrd][scnd]);
			scnd++;
		}
			free(data[thrd]);
			scnd = 0;
			thrd++;
	}
	free(data);
}

void	free_point_arr(t_mlx_ptrs *mlx_ptrs)
{
	t_point	**point_arr;
	int	width;
	int	height;

	width = 0;
	height = 0;
	point_arr = mlx_ptrs->data->point;

	while (height < mlx_ptrs->data->vert)
	{
		free(point_arr[height]);
		height++;
	}
	free(point_arr);
}
