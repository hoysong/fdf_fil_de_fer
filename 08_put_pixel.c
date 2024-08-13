/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 01:38:56 by hoysong           #+#    #+#             */
/*   Updated: 2024/08/13 14:12:05 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

static int	calc_rgb(int start, int end, float precent)
{
	int	updown;

	updown = ((start - end) * precent);
	if (start < end)
		updown *= -1;
	if (start > end)
		updown *= -1;
	return (start + updown);
}

int	get_new_rgb(t_color *start, t_color *end, float precent)
{
	int				new_rgb;
	unsigned char	*new_ptr;

	new_rgb = 0;
	new_ptr = (unsigned char *)&new_rgb;
	*new_ptr = calc_rgb(start->blue, end->blue, precent);
	new_ptr++;
	*new_ptr = calc_rgb(start->green, end->green, precent);
	new_ptr++;
	*new_ptr = calc_rgb(start->red, end->red, precent);
	return (new_rgb);
}
