/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_img_buf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:58:31 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/27 14:18:16 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"
void  my_mlx_pixel_put(t_mlx_ptrs *data, int x, int y, int color)
{
	char *dst;
	
	dst = data->img_data->addr + (y * data->img_data->size_line + x * (data->img_data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

//void	put_image(int x, int y, t_mlx_ptrs *l, int color)
//{
//	int pixel = (y * l->line_bytes) + (x * 4);
//	*(int *)(l->img_data->addr) = color;
//
//	char	*put;
//	if (y <= 0)
//		while (y < 0)
//			y += 1;
//	else if (y >= 100)
//		while (y >= 1000)
//			y -= 1;
//	if (x < 0)
//		while (x < 0)
//			x += 1;
//	else if (x >= 1000)
//		while (x >= 1000)
//			x -= 1;
//	put = (char *)(l->data->int_arr[0][0][0] + (y * l->img_data->size_line + x * (l->img_data->bits_per_pixel / 8)));
//	*(unsigned int *)put = color;
//}
