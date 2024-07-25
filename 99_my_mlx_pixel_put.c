/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_my_mlx_pixel_put.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 06:23:56 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/26 06:24:14 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

void	my_mlx_pixel_put(t_img_strc *img_data, int x, int y, int color)
{
	char	*dst;

	dst = img_data->addr
		+ (y * img_data->size_line + x * (img_data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
