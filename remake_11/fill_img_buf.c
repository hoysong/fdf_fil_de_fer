/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_img_buf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:58:31 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/27 19:25:43 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"
#include <math.h>
void  my_mlx_pixel_put(t_mlx_ptrs *data, int x, int y, int color)
{
	char *dst;

	dst = data->img_data->addr + (y * data->img_data->size_line + x * (data->img_data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	qter_view(int point_x, int point_y, t_mlx_ptrs *mlx_ptrs)
{
	int	dot_x;
	int	dot_y;
	int	prev_z;
	int	point_x1;
	int	point_y1;

	prev_z = mlx_ptrs->data->int_arr[0][point_x][point_y];

	dot_x = point_y * cos(30) + prev_z * sin(30);
	dot_y = -point_y * sin(30) + prev_z * cos(30);
	my_mlx_pixel_put(mlx_ptrs, dot_x, dot_y, 0xffffff);
}

void	make_trigon(t_mlx_ptrs *mlx_ptrs)
{
	int	x;
	int	y;
	int	***pars_arr;
	int gap;
	x = 0;
	gap = 10;
//	x = mlx_ptrs->data->vert;
//	y = mlx_ptrs->data->height;

	while (x < mlx_ptrs->data->vert)
	{
		while(y < mlx_ptrs->data->horiz)
		{
			qter_view(x, y, mlx_ptrs);
			y++;
		}
		y = 0;
		x++;
	}
}
