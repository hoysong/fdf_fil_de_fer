/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 05:31:06 by hoysong           #+#    #+#             */
/*   Updated: 2024/08/13 02:03:04 by hoysong          ###   ########.fr       */
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

static int	calc_color(int strt_clr, int end_clr, float precent)
{
	int		new_color;
	t_color	start_rgb;
	t_color	end_rgb;

	start_rgb = get_rgb(strt_clr);
	end_rgb = get_rgb(end_clr);
	new_color = get_new_rgb(&start_rgb, &end_rgb, precent);
	return (new_color);
}

void	put_pixel(t_brzm brzm, t_point start, t_point end, t_img_strc *img_data)
{
	float	start_end_dist;
	float	brzm_dist;
	int		new_color;

	start_end_dist = get_dist(start, end);
	brzm_dist = strt_brzm_dist(brzm, start);
	new_color = calc_color(start.color, end.color, brzm_dist / start_end_dist);
	my_mlx_pixel_put(img_data, brzm.x, brzm.y, new_color);
	return ;
}
