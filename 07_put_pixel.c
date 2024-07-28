/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 05:31:06 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/28 15:42:02 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

static float	get_dist(t_point start, t_point end)
{
	float	x1;
	float	y1;
	float	x2;
	float	y2;
	float	btw_start_end;

	x1 = start.x;
	y1 = start.y;
	x2 = end.x;
	y2 = end.y;
	btw_start_end = sqrt(pow(x1 - x2, 2) + pow(y2 - y1, 2));
	printf("start / end : %f\n", btw_start_end);
	return (btw_start_end);
}
static float	strt_brzm_dist(t_brzm start, t_point end)
{
	float	x1;
	float	y1;
	float	x2;
	float	y2;
	float	btw_start_end;

	x1 = start.x;
	y1 = start.y;
	x2 = end.x;
	y2 = end.y;
	btw_start_end = sqrt(pow(x1 - x2, 2) + pow(y2 - y1, 2));
	printf("start / brzm: %f\n", btw_start_end);
	return (btw_start_end);
}

static t_color	get_rgb(int hex_color)
{
	t_color	rgb;

	rgb.red = *((unsigned char *)&hex_color + 2);
	rgb.green = *((unsigned char *)&hex_color + 1);
	rgb.blue = *((unsigned char *)&hex_color);

	return (rgb);
}

static int	get_new_rgb(t_color *start, t_color *end, float precent)
{
	//int		new_rgb;
	//char	*rgb_ptr;

	//new_rgb = 0;
	//rgb_ptr = (char *)&new_rgb;

	///* get blue */
	//*rgb_ptr = (start->blue);
	//rgb_ptr++;

	///* get green */
	//*rgb_ptr = (start->green);
	//rgb_ptr++;

	///* get red */
	//*rgb_ptr = (start->red);
	//rgb_ptr++;

	int		new_rgb;
	int		diff_color;
	unsigned char	*new_ptr;
	char	*start_ptr;
	char	*end_ptr;
	int		updown;

	new_rgb = 0;
	new_ptr = (unsigned char *)&new_rgb;
	printf("precent??: %f\n", precent);

	updown = ((start->blue - end->blue) * precent);
	if (start->blue < end->blue)
		updown *= -1;
	if (start->blue > end->blue)
		updown *= -1;
	*new_ptr = start->blue + updown;
	//printf("start - end: %x\n", start->blue - end->blue);
	//printf("%x\n", *new_ptr);
	new_ptr++;

	printf(" !!!new_rgb: %x\n", new_rgb);
	return (new_rgb);
}

static int	calc_color(int strt_clr, int end_clr, float precent)
{
	int		new_color;
	t_color	start_rgb;
	t_color	end_rgb;

	printf("precent: %f\n", precent);
	start_rgb = get_rgb(strt_clr);
	end_rgb = get_rgb(end_clr);

	printf("	get_rgb\n");
	printf("red   start: %x, end: %x\n", start_rgb.red, end_rgb.red);
	printf("red   start: %x, end: %x\n", start_rgb.red, end_rgb.red);
	printf("green start: %x, end: %x\n", start_rgb.green, end_rgb.green);
	printf("blue  start: %x, end: %x\n", start_rgb.blue, end_rgb.blue);

	new_color = get_new_rgb(&start_rgb, &end_rgb, precent);
	return (new_color);
}

void	put_pixel(t_brzm brzm, t_point start, t_point end, t_img_strc *img_data)
{
	float	start_end_dist;
	float	brzm_dist;
	int		new_color;

	printf("	== put_pixel ==\n");
	printf("origin | start: %x, end:%x\n", start.color, end.color);
	start_end_dist = get_dist(start, end);
	brzm_dist = strt_brzm_dist(brzm, start);

	new_color = calc_color(start.color, end.color, brzm_dist / start_end_dist);
	printf("\n");
	my_mlx_pixel_put(img_data, brzm.x, brzm.y, new_color);
	return ;
}
// 6.	점을 찍어가며 end에 가까워지는 비율 만큼 color값도 end에 가까워지게 바꾸면 될 것이다.
//
// 7.	시작점은 brzm.x, y일 것이다.
// 		끝점은 그럼 그대로 end일 것이다.
