/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:00:47 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/25 08:42:08 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

static void Bresenham_y(t_point start, t_point end, t_img_strc *img_data)
{
	t_brzm brzm;

	brzm.x = start.x;
	brzm.y = start.y;
	brzm.dx = end.x - start.x;
	brzm.dy = end.y - start.y;
	brzm.P = 2 * brzm.dx - brzm.dy;  // P1(초기값) 설정
	brzm.i_val = 1;
	if (brzm.dx < 0)
	{
		brzm.i_val = -1;
		brzm.dx = -brzm.dx;
	}
	while (brzm.y <= end.y)
	{
		my_mlx_pixel_put(img_data, brzm.x, brzm.y, 0x995555);
		brzm.y++;  // x는 매 좌표마다 증가
		if (brzm.P < 0)  // Pnext 구하는 부분
			brzm.P = brzm.P + 2 * brzm.dx;
		else {
			brzm.P = brzm.P + 2 * brzm.dx - 2 * brzm.dy;
			brzm.x += brzm.i_val;
		}
	}
}

static void Bresenham_x(t_point start, t_point end, t_img_strc *img_data)
{
	t_brzm brzm;
	brzm.x = start.x;
	brzm.y = start.y;
	brzm.dx = end.x - start.x;
	brzm.dy = end.y - start.y;
	brzm.P = 2 * brzm.dy - brzm.dx;  // P1(초기값) 설정
	brzm.i_val = 1;

	if (brzm.dy < 0)
	{
		brzm.i_val = -1;
		brzm.dy = -brzm.dy;
	}
	while (brzm.x <= end.x)
	{
		my_mlx_pixel_put(img_data, brzm.x, brzm.y, 0x00ff00);
		brzm.x++;  // x는 매 좌표마다 증가
		if (brzm.P < 0)  // Pnext 구하는 부분
			brzm.P = brzm.P + 2 * brzm.dy;
		else
		{
			brzm.P = brzm.P + 2 * brzm.dy - 2 * brzm.dx;
			brzm.y += brzm.i_val;
		}
	}
}

static void brzm(t_point start, t_point end, t_img_strc *img_data)
{
		if (abs(end.y - start.y) < abs(end.x - start.x))
		{
			if (start.x > end.x)
			Bresenham_x(end, start, img_data);
			else
			Bresenham_x(start, end, img_data);
		}
		else
		{
		if (start.y > end.y)
			Bresenham_y(end, start, img_data);
		else
			Bresenham_y(start, end, img_data);
		}
}

void	draw_line(t_img_strc *img_data, t_prs_data *prs_data)
{
	int	i;
	int	j;
	t_point **point;
	point = prs_data->point;

	i = 0;
	while(i < prs_data->vert)
	{
		j = 0;
		while(j < prs_data->horiz)
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
