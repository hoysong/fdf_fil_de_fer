/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_make_view.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 02:52:37 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/12 04:53:51 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

//put pixel in img buffer
static void	my_mlx_pixel_put(t_img_strc *img_data, int x, int y, int color)
{
	char *dst;

	dst = img_data->addr + (y * img_data->size_line + x * (img_data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	ft_rotate_z(int *x, int *y, double z_angle)
{
	t_point	prev;

	prev.x = *x;
	prev.y = *y;
	*x = (prev.x * cos(z_angle) - prev.y * sin(z_angle)) * 1;
	*y = (prev.x * sin(z_angle) + prev.y * cos(z_angle)) * 1;
}


static void pixel_put(int x, int y, t_img_strc *img_data, t_prs_data *prs_data)
{
	int		i;
	int		j;
	t_point	**point;
	
	i = 0;
	x *= -1;
	y *= -1;
	point = prs_data->point;
	while(i < prs_data->vert)
	{
		j = 0;
		while(j < prs_data->horiz)
		{
			point[i][j].x += x;
			point[i][j].y += y;
			my_mlx_pixel_put(img_data, point[i][j].x, point[i][j].y, point[i][j].color);
			j++;
		}
		i++;
	}
}
static void	get_low_num_2(t_prs_data *prs_data, t_img_strc *img_data)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (i < prs_data->horiz)
	{
		if (x > prs_data->point[0][i].x)
			x = prs_data->point[0][i].x;
		if (y > prs_data->point[0][i].y)
			y = prs_data->point[0][i].y;
		i++;
	}
	i = 0;
	while (i < prs_data->vert)
	{
		if (x > prs_data->point[0][i].x)
			x = prs_data->point[0][i].x;
		if (y > prs_data->point[0][i].y)
			y = prs_data->point[0][i].y;
		i++;
	}
//	db_point_xy_prs_data(prs_data);
	pixel_put(x, y, img_data, prs_data);
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
			ft_rotate_z(&(point[i][j].x), &(point[i][j].y), 45 * M_PI / 180); //바라보는 기준 45도 회전
			point[i][j].z *= 5; // z 1당 높이값을 지정.
			point[i][j].y += point[i][j].z; // z에 곱한 값을 y에 적용한다.
			point[i][j].y *= 0.5; // y의 값에 0.5와 같이 곱셈을 하여 찌부시킨다.
			j++;
		}
		i++;
	}
	get_low_num_2(prs_data, img_data);
}
