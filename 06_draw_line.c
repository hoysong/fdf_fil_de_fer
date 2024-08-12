/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:00:47 by hoysong           #+#    #+#             */
/*   Updated: 2024/08/13 02:04:48 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

static void	bresenham_y(t_point start, t_point end, t_img_strc *img_data)
{
	t_brzm	brzm;

	brzm.x = start.x;
	brzm.y = start.y;
	brzm.dx = end.x - start.x;
	brzm.dy = end.y - start.y;
	brzm.p = 2 * brzm.dx - brzm.dy;
	brzm.i_val = 1;
	if (brzm.dx < 0)
	{
		brzm.i_val = -1;
		brzm.dx = -brzm.dx;
	}
	while (brzm.y <= end.y)
	{
		put_pixel(brzm, start, end, img_data);
		brzm.y++;
		if (brzm.p < 0)
			brzm.p = brzm.p + 2 * brzm.dx;
		else
		{
			brzm.p = brzm.p + 2 * brzm.dx - 2 * brzm.dy;
			brzm.x += brzm.i_val;
		}
	}
}

static void	bresenham_x(t_point start, t_point end, t_img_strc *img_data)
{
	t_brzm	brzm;

	brzm.x = start.x;
	brzm.y = start.y;
	brzm.dx = end.x - start.x;
	brzm.dy = end.y - start.y;
	brzm.p = 2 * brzm.dy - brzm.dx;
	brzm.i_val = 1;
	if (brzm.dy < 0)
	{
		brzm.i_val = -1;
		brzm.dy = -brzm.dy;
	}
	while (brzm.x <= end.x)
	{
		put_pixel(brzm, start, end, img_data);
		brzm.x++;
		if (brzm.p < 0)
			brzm.p = brzm.p + 2 * brzm.dy;
		else
		{
			brzm.p = brzm.p + 2 * brzm.dy - 2 * brzm.dx;
			brzm.y += brzm.i_val;
		}
	}
}

static void	brzm(t_point start, t_point end, t_img_strc *img_data)
{
	if (abs(end.y - start.y) < abs(end.x - start.x))
	{
		if (start.x > end.x)
			bresenham_x(end, start, img_data);
		else
			bresenham_x(start, end, img_data);
	}
	else
	{
		if (start.y > end.y)
			bresenham_y(end, start, img_data);
		else
			bresenham_y(start, end, img_data);
	}
}

void	draw_line(t_img_strc *img_data, t_prs_data *prs_data)
{
	int		i;
	int		j;
	t_point	**point;

	point = prs_data->point;
	i = 0;
	while (i < prs_data->vert)
	{
		j = 0;
		while (j < prs_data->horiz)
		{
			if (j < prs_data->horiz - 1)
				brzm(point[i][j], point[i][j + 1], img_data);
			if (i < prs_data->vert - 1)
				brzm(point[i][j], point[i + 1][j], img_data);
			j++;
		}
		i++;
	}
}
