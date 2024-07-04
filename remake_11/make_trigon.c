/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_trigon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:58:31 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/04 20:09:01 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"
#include <math.h>

static void	my_mlx_pixel_put(t_img_strc *img_data, int x, int y, int color)
{
	char *dst;

	dst = img_data->addr + (y * img_data->size_line + x * (img_data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	ft_rotate_x(int *y, int *z, double x_angle)
{
	int	prev_y;

	prev_y = *y;
	*y = prev_y * cos(x_angle) + *z * sin(x_angle);
	*z = prev_y * -sin(x_angle) + *z * cos(x_angle);
}

static void	make_gap(t_prs_info *prs_info)
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
			prs_info->point[y][x].z = &(prs_info->int_arr[0][y][x]);
			x++;
		}
		x = 0;
		y++;
	}
	return ;
}

void	make_trigon(t_mlx_ptrs *mlx_ptrs)
{
	int		x;
	int		y;
	int		***pars_arr;
	t_point	**point_arr;

	x = 0;
	y = 0;
	point_arr = mlx_ptrs->data->point;

	make_gap(mlx_ptrs->data);
	rotate_points(mlx_ptrs);

	while (x < mlx_ptrs->data->vert)
	{
		while(y < mlx_ptrs->data->horiz)
		{
			my_mlx_pixel_put(mlx_ptrs->img_data, point_arr[y][x].x, point_arr[y][x].y, *(point_arr[y][x].color));
			y++;
		}
		y = 0;
		x++;
	}
}
