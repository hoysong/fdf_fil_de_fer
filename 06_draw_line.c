/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:00:47 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/25 08:18:10 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

static void Bresenham_y(int x0, int y0, int x1, int y1, t_img_strc *img_data)
{
	int	x = x0;
	int	y = y0;
	int	dx = x1 - x0;
	int	dy = y1 - y0;
	int	P = 2 * dx - dy;  // P1(초기값) 설정
	int xi = 1;

		if (dx < 0)
		{
			xi = -1;
			dx = -dx;
		}
	while (y <= y1)
	{
		my_mlx_pixel_put(img_data, x, y, 0xffffff);
		y++;  // x는 매 좌표마다 증가
		if (P < 0)  // Pnext 구하는 부분
			P = P + 2 * dx;
		else
		{
			P = P + 2 * dx - 2 * dy;
			x += xi;
		}
	}
}

static void Bresenham_x(int x0, int y0, int x1, int y1, t_img_strc *img_data)
{
	int	x = x0;
	int	y = y0;
	int	dx = x1 - x0;
	int	dy = y1 - y0;
	int	P = 2 * dy - dx;  // P1(초기값) 설정
	int	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	while (x <= x1)
	{
		my_mlx_pixel_put(img_data, x, y, 0xffffff);
		x++;  // x는 매 좌표마다 증가
		if (P < 0)  // Pnext 구하는 부분
			P = P + 2 * dy;
		else
		{
			P = P + 2 * dy - 2 * dx;
			y += yi;
		}
	}
}

//static void brzm_2(int x0, int y0, int x1, int y1, t_img_strc *img_data)
static void brzm(t_point start, t_point end, t_img_strc *img_data)
{
		if (abs(end.y - start.y) < abs(end.x - start.x))
		{
			if (start.x > end.x)
			Bresenham_x(end.x, end.y, start.x, start.y, img_data);
			else
			Bresenham_x(start.x, start.y, end.x, end.y, img_data);
		}
		else
		{
		if (start.y > end.y)
			Bresenham_y(end.x, end.y, start.x, start.y, img_data);
		else
			Bresenham_y(start.x, start.y, end.x, end.y, img_data);
		}
}

//static void brzm_1()
//{
//	return ;
//}

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
