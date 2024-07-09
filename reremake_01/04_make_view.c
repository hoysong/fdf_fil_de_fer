/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_make_view.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 02:52:37 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/10 05:29:31 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

//void set_point_location(t_prs_data *prs_data)
//{
//	int	i;
//	int	j;
//	t_point		**point;
//
//	i = 0;
//	point = prs_data->point;
//	while(i < prs_data->vert)
//	{
//		j = 0;
//		while(j < prs_data->horiz)
//		{
//			rotate_x(&(point[i][j]));
//			rotate_y(&(point[i][j]));
//			rotate_z(&(point[i][j]));
//			j++;
//		}
//		i++;
//	}
//}

void rotate_z(t_point *a)
{
	int	tmp;
	int	gamma;

	gamma = 0;
	tmp = a->x;
	a->x = tmp * cos(gamma) - a->y * sin(gamma);
	a->y = tmp * sin(gamma) + a->y * cos(gamma);
}

void rotate_y(t_point *a)
{
	int	tmp;
	int	tetha;

	tetha = 0;
	tmp = a->x;
	a->x = tmp * cos(tetha) + a->z * sin(tetha);
	a->z = a->z * cos(tetha) - tmp * sin(tetha);
}

void rotate_x(t_point *a)
{
	int	tmp;
	int	alpha;
	
	alpha = 0;
	tmp = a->y;
	a->y = tmp * cos(alpha) - a->z * sin(alpha);
	a->z = tmp * sin(alpha) + a->z * cos(alpha);
	//a->y = tmp * cos(alpha) - fdf->a->z * sin(alpha);
	//a->z = tmp * sin(alpha) + fdf->a->z * cos(alpha);
}

//static int	get_low_num(int x, int y)
//{
//}

static void	my_mlx_pixel_put(t_img_strc *img_data, int x, int y, int color)
{
	char *dst;

	dst = img_data->addr + (y * img_data->size_line + x * (img_data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void iso_prjc(t_img_strc *img_data, t_prs_data *prs_data)
{
	int		i;
	int		j;
	int		tmp;
	t_point	**point;
	
	i = 0;
	point = prs_data->point;
	while(i < prs_data->vert)
	{
		j = 0;
		tmp = point[i][j].x;
		while(j < prs_data->horiz)
		{
			point[i][j].x = (tmp - point[i][j].y) * cos(0.523599);
			point[i][j].y = (tmp + point[i][j].y) * sin(0.523599) - point[i][j].z;
			my_mlx_pixel_put(img_data, point[i][j].x, point[i][j].y, point[i][j].color);
			j++;
		}
		i++;
	}
}
