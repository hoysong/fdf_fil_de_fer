/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_point_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:36:32 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/30 01:44:38 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"

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

static void	insert_int_to_point_arr(t_mlx_ptrs *mlx_ptrs)
{
	int	***int_arr;
	int	x;
	int	y;
	t_point	**point;

	point = mlx_ptrs->data->point;
	int_arr = mlx_ptrs->data->int_arr;
	x = 0;
	y = 0;
	while(y < mlx_ptrs->data->vert)
	{
		while(x < mlx_ptrs->data->vert)
		{
			point[y][x].x = x;
			point[y][x].y = y;
			point[y][x].z = &(int_arr[0][y][x]);
			point[y][x].color = &(int_arr[1][y][x]);
			x++;
		}
		x = 0;
		y++;
	}
	printf("inner\n");
	debug_point_arr(mlx_ptrs);
//	free_point_arr(mlx_ptrs);
}

static t_point	**make_point_arr(t_mlx_ptrs	*mlx_ptrs)
{
	t_point	**point_arr;
	int	width;
	int	height;

	width = 0;
	height = 0;

	printf("vert?: %d\n", mlx_ptrs->data->vert);
	point_arr = (t_point **)malloc(sizeof(t_point *) * mlx_ptrs->data->vert);
	if (point_arr == 0)
		return (0);

	while(height < mlx_ptrs->data->vert)
	{
		point_arr[height] = (t_point *)malloc(sizeof(t_point) * mlx_ptrs->data->horiz);
		height++;
	}
	return (point_arr);
}

t_point	**int_to_point(t_mlx_ptrs *mlx_ptrs)
{
	t_point	**point_arr;

	mlx_ptrs->data->point = make_point_arr(mlx_ptrs);
	insert_int_to_point_arr(mlx_ptrs);
	printf("\nout\n");
	debug_point_arr(mlx_ptrs);

	return (point_arr);
}
