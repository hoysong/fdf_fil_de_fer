/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_iso_prjc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 02:52:37 by hoysong           #+#    #+#             */
/*   Updated: 2024/08/16 19:34:30 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

static void	low_num_apply(t_mv mv, t_prs_data *prs_data)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (i < prs_data->vert)
	{
		j = 0;
		while (j < prs_data->horiz)
		{
			prs_data->point[i][j].x += mv.mv_x;
			prs_data->point[i][j].y += mv.mv_y;
			j++;
		}
		i++;
	}
}

static void	get_low_num(
	int x, int y, t_prs_data *prs_data, t_img_strc *img_data)
{
	static t_mv	mv;

	if (img_data == 0)
	{
		if (mv.mv_x > x && x < 0)
			mv.mv_x = x;
		if (mv.mv_y > y && y < 0)
			mv.mv_y = y;
	}
	else
	{
		mv.mv_x *= -1;
		mv.mv_y *= -1;
		low_num_apply(mv, prs_data);
	}
}

static void	ft_rotate_z(int *x, int *y, double z_angle)
{
	t_point	prev;

	prev.x = *x;
	prev.y = *y;
	*x = (prev.x * cos(z_angle) - prev.y * sin(z_angle)) * 70;
	*y = (prev.x * sin(z_angle) + prev.y * cos(z_angle)) * 70;
}

void	iso_prjc(t_img_strc *img_data, t_prs_data *prs_data)
{
	int		i;
	int		j;
	t_point	**point;

	i = 0;
	point = prs_data->point;
	while (i < prs_data->vert)
	{
		j = 0;
		while (j < prs_data->horiz)
		{
			point[i][j].y *= -1;
			point[i][j].z *= -1;
			ft_rotate_z(&(point[i][j].x), &(point[i][j].y), 45 * M_PI / 180);
			point[i][j].z *= 40;
			point[i][j].y += point[i][j].z;
			point[i][j].y *= 0.58;
			get_low_num(point[i][j].x, point[i][j].y, prs_data, 0);
			j++;
		}
		i++;
	}
	get_low_num(0, 0, prs_data, img_data);
}
