/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_img_buf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:58:31 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/29 17:33:30 by hoysong          ###   ########.fr       */
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

void make_gap(t_mlx_ptrs *mlx_ptrs)
{
	t_prs_info *prs_info;
	int	y;
	int	x;
	prs_info = mlx_ptrs->data;
	x = 0;
	y = 0;
	while (y < prs_info->horiz )
	{
		x = 0;
		while (x < prs_info->vert)
		{
			prs_info->int_arr[2][x][y] = x * 10;
			//prs_info->int_arr[2][x][y] = x * 10;
			//prs_info->int_arr[2][x][y] = x * 10;
			//(var->offset[y][x]).x = x * var->gap;
			//(var->offset[y][x]).y = y * var->gap;
			//(var->offset[y][x]).z = var->map[y][x];
			x++;
		}
		y++;
	}
}

//void	qter_view(int point_x, int point_y, t_mlx_ptrs *mlx_ptrs)
//{
//	int	dot_x;
//	int	dot_y;
//	int	prev_z;
//	int	point_x1;
//	int	point_y1;
//
//	prev_z = mlx_ptrs->data->int_arr[2][point_x][point_y];
//
//	dot_x = point_y * cos(30) + prev_z * sin(30);
//	dot_y = -point_y * sin(30) + prev_z * cos(30);
//	my_mlx_pixel_put(mlx_ptrs, dot_x, dot_y, 0xffffff);
////new_y = prev_y * cos(각도) + prev_z * sin(각도);
////new_z = -prev_y * sin(각도) + prev_z * cos(각도);
////new_x = prev_x * cos(각도) - prev_z * sin(각도);
////new_z = prev_x * sin(각도) + prev_z * cos(각도);
////new_x = prev_x * cos(각도) + prev_y * sin(각도);
////new_y = -prev_x * sin(각도) + prev_y * cos(각도);
//
//}
void	qter_view(int prev_x, int prev_y, t_mlx_ptrs *mlx_ptrs)
{
	int new_x;
	int	new_y;
	int	new_z;
	int prev_z;

	prev_z = mlx_ptrs->data->int_arr[2][prev_x][prev_y];

	new_x = prev_x * cos(30) + prev_z * sin(30);
	new_y = -prev_y * sin(30) + prev_z * cos(30);

	prev_x = new_x;
	prev_y = new_y;

	new_x = prev_x * cos(30) - prev_z * sin(30);
	new_z = prev_x * sin(30) + prev_z * cos(30);

	prev_x = new_x;

	new_x = prev_x * cos(30) + prev_y * sin(30);
	new_y = -prev_x * sin(30) + prev_y * cos(30);

	my_mlx_pixel_put(mlx_ptrs, new_x, new_y, 0xffffff);
}

//void qter_view_x(t_mlx_ptrs *mlx_ptrs)
//{
//	int	***prs_arr;
//	int	x;
//	int y;
//
//	prs_arr = mlx_ptrs->data->int_arr;
//	x = 0;
//	y = 0;
//	while(x < mlx_ptrs->data->vert)
//	{
//		while(y < mlx_ptrs->data->vert)
//		{
//			prs_arr[0][x][y];
//			y++;
//		}
//		y = 0;
//		x ++;
//	}
//}

//void qter_view()
//{
//}

void	make_trigon(t_mlx_ptrs *mlx_ptrs)
{
	int	x;
	int	y;
	int	***pars_arr;
	int gap;
	x = 0;
	y = 0;
	gap = 10;
//	x = mlx_ptrs->data->vert;
//	y = mlx_ptrs->data->height;
	make_gap(mlx_ptrs);

	while (x < mlx_ptrs->data->vert)
	{
		while(y < mlx_ptrs->data->horiz)
		{
//			my_mlx_pixel_put(mlx_ptrs, x, y, 0xffffff);
			qter_view(x, y, mlx_ptrs);
			y++;
		}
		y = 0;
		x++;
	}
}
