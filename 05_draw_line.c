/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:00:47 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/16 04:01:27 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

//void	bresen()
//{
//	int width = abs(endPosition.X - startPosition.X);
//	int height = abs(endPosition.Y - startPosition.Y);
//	
//	// 여기서 부터 구현
////	SetPixel(startPosition, InColor);
//	int x = startPosition.X;
//	int y = startPosition.Y;
//	
//	int YValue = InEndPos.Y >= 0 ? -1 : 1;
//	int XValue = InEndPos.X >= 0 ? 1 : -1;
//	
//	// 1,4,5,8 팔분면일 경우
//	if (width > height)
//	{
//		int det = (2 * height) - width; // 판별식
//		for (x = startPosition.X; x != endPosition.X; x += XValue)
//		{
//			if (det < 0)
//			{
//				det += 2 * height;
//			}
//			else
//			{
//				y += YValue;
//				det += (2 * height - 2 * width);
//			}
//			SetPixel(ScreenPoint(x, y), InColor);
//		}
//	}
//	// 2,3,6,7 팔분면일 경우
//	else
//	{
//		int det = (2 * width) - height; // 판별식
//		for (y = startPosition.Y; y != endPosition.Y; y += YValue)
//		{
//			if (det < 0)
//			{
//				det += 2 * width;
//			}
//			else
//			{
//				x += XValue;
//				det += (2 * width - 2 * height);
//			}
//			SetPixel(ScreenPoint(x, y), InColor);
//		}
//	}
//}
//void plotLineLow(int x0, int y0, int x1, int y1, t_img_strc *img_data)
//{
//	int	dx = x1 - x0;
//	int	dy = y1 - y0;
//	int	yi = 1;
//	if (dy < 0)
//	{
//	    yi = -1;
//	    dy = -dy;
//	}
//	int	D = (2 * dy) - dx;
//	int	y = y0;
//	
//	int	x = 0;
//	while (x < (x0 || x1))
//	{
//		my_mlx_pixel_put(img_data, x, y, 0xffffff);
//	    if (D > 0)
//		{
//			y = y + yi;
//			D = D + (2 * (dy - dx));
//		}
//	    else
//			D = D + 2*dy;
//		x++;
//	}
//}
//
//void Bresenham(int x0, int y0, int x1, int y1, t_img_strc *img_data)
//{
//	if (abs(y1 - y0) < abs(x1 - x0))
//		if (x0 > x1)
//			plotLineLow(x1, y1, x0, y0, img_data);
//		else
//			plotLineLow(x0, y0, x1, y1, img_data);
//	else if (y0 > y1)
//			printf("hihi");
//			//plotLineHigh(x1, y1, x0, y0, img_data);
//		else
//			printf("hihi");
//			//plotLineHigh(x0, y0, x1, y1, img_data);
//}
void Bresenham_y(int x0, int y0, int x1, int y1, t_img_strc *img_data)
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

void Bresenham_x(int x0, int y0, int x1, int y1, t_img_strc *img_data)
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
void brzm(int x0, int y0, int x1, int y1, t_img_strc *img_data)
{
		if (abs(y1 - y0) < abs(x1 - x0))
		{
		        if (x0 > x1)
			Bresenham_x(
					x1,
					y1,
					x0,
					y0,
					img_data
					);
		        else
			Bresenham_x(
					x0,
					y0,
					x1,
					y1,
					img_data
					);
		}
		else
		{
		        if (y0 > y1)
			Bresenham_y(
					x1,
					y1,
					x0,
					y0,
					img_data
					);
		        else
			Bresenham_y(
					x0,
					y0,
					x1,
					y1,
					img_data
					);
		}
}


void	draw_line(t_img_strc *img_data, t_prs_data *prs_data)
{
	int	i;
	int	j;
	t_point **point;
	point = prs_data->point;

	i = 0;
	while(i < prs_data->vert - 1)
	{
		j = 0;
		while(j < prs_data->horiz - 1)
		{
			brzm(point[i][j].x, point[i][j].y, point[i][j + 1].x, point[i][j + 1].y, img_data);
			brzm(point[i][j].x, point[i][j].y, point[i + 1][j].x, point[i + 1][j].y, img_data);
//			Bresenham_x(
//					point[i][j].x,
//					point[i][j].y,
//					point[i][j + 1].x,
//					point[i][j + 1].y,
//					img_data
//					);
			j++;
		}
		i++;
	}
}
