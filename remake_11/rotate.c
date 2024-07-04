/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:19:53 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/04 23:27:52 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"
static void	ft_rotate_x(int *y, int *z, double x_angle)
{
	int	prev_y;

	prev_y = *y;
	*y = prev_y * cos(x_angle) + *z * sin(x_angle);
	*z = prev_y * -sin(x_angle) + *z * cos(x_angle);
}

static void	ft_rotate_y(int *x, int *z, double y_angle)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(y_angle) + *z * sin(y_angle);
	*z = prev_x * -sin(y_angle) + *z * cos(y_angle);
}

static void	ft_rotate_z(int *x, int *y, double z_angle)
{
	t_point	prev;

	prev.x = *x;
	prev.y = *y;
	*x = prev.x * cos(z_angle) - prev.y * sin(z_angle);
	*y = prev.x * sin(z_angle) + prev.y * cos(z_angle);
}

//static void	to_pstv(t_prs_info *prs_data)
//{
//}

static t_mv	get_lower(t_point *point, int stat)
{
	static t_mv	mv;

	if (stat == 0)
	{
		if (mv.mv_x > point->x)
			mv.mv_x = point->x;
		if (mv.mv_y > point->y)
			mv.mv_y = point->y;
	}
	return(mv);
}

static void	mv_points(t_mlx_ptrs *mlx_ptrs, t_mv mv)
{
	int	x;
	int	y;
	t_point	**point;

	y = 0;
	printf("low_x: %d\n", mv.mv_x);
	printf("low_y: %d\n", mv.mv_y);
	point = mlx_ptrs->data->point;
	while(y < mlx_ptrs->data->vert)
	{
		x = 0;
		while(x < mlx_ptrs->data->horiz)
		{
			point[y][x].x += 80;
			x++;
		}
		y++;
	}
}

void	rotate_points(t_mlx_ptrs *mlx_ptrs)
{
	int		x;
	int		y;

	t_point	**point;

	y = 0;
	point = mlx_ptrs->data->point;
	while (y < mlx_ptrs->data->vert)
	{
	x = 0;
		while(x < mlx_ptrs->data->horiz)
		{
			ft_rotate_x(&(point[y][x].y), &(point[y][x].x), 70);
			ft_rotate_y(&(point[y][x].x), &(*(point[y][x].z)), 120);
			ft_rotate_z(&(point[y][x].x), &(point[y][x].y), 120);
			get_lower(&(point[y][x]), 0);
			x++;
		}
		y++;
	}
	mv_points(mlx_ptrs, get_lower(&(point[x][y]), 1));
	debug_point_arr(mlx_ptrs);
}
