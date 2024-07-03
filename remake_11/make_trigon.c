/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_trigon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:58:31 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/04 03:27:28 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"
//#include <math.h>
void	my_mlx_pixel_put(t_mlx_ptrs *data, int x, int y, int color)
{
	char *dst;

	dst = data->img_data->addr + (y * data->img_data->size_line + x * (data->img_data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	make_gap(t_prs_info *prs_info)
{
	int	x;
	int	y;
	int gap;

	gap = 10;
	x = 0;
	y = 0;
	while (y < prs_info->vert)
	{
		while (x < prs_info->horiz)
		{
			prs_info->point[y][x].x = x * gap;
			prs_info->point[y][x].y = y * gap;
			prs_info->point[y][x].z = prs_info->int_arr[y][x];
			x++;
		}
		x = 0;
		y++;
	}
	return ;
}


void	make_trigon(t_mlx_ptrs *mlx_ptrs)
{
	int	x;
	int	y;
	int	***pars_arr;
	int gap;
	x = 0;
	y = 0;
	gap = 10;
	make_gap(mlx_ptrs->data);

	while (x < mlx_ptrs->data->vert)
	{
		while(y < mlx_ptrs->data->horiz)
		{
//			qter_view(x, y, mlx_ptrs);
			my_mlx_pixel_put(mlx_ptrs, x, y, 0xffffff);
			y++;
		}
		y = 0;
		x++;
	}
}
