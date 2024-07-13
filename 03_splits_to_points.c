/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_splits_to_points.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 01:53:43 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/14 07:18:00 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

static int	color_atoi(char *src)
{
	int	int_value;

	int_value = 0;
	if (*src == ',')
		src++;
	if (*src == '0' && *(src + 1) == 'x')
		src = src + 2;
	while (*src)
	{
		if ('0' <= *src && *src <= '9')
			int_value = (int_value * 16) + (*src - '0');
		if ('a' <= *src && *src <= 'f')
			*src = ft_toupper(*src);
		if ('A' <= *src && *src <= 'F')
			int_value = (int_value * 16) + (*src - 55);
		++src;
	}
	if (int_value == 0)
		return (0xFFFFFF);
	return (int_value);
}

static int	z_atoi(t_point *point_arr, char *z)
{
	int	z_value;

	z_value = 0;
	while (*z && *z != ',' && *z != '\n')
	{
		z_value = (z_value * 10) + (*z - '0');
		z++;
	}
	point_arr->color = color_atoi(z);
	return (z_value);
}

t_point	**splits_to_points(t_prs_data *prs_data, char ***splits)
{
	int	i;
	int	j;
	t_point	**point_arr;

	point_arr = (t_point **)malloc(sizeof(t_point *) * prs_data->file_lines);
	if(point_arr == 0)
		return (0);
	i = 0;
	j = 0;
	// point_arr에 malloc을 해주는 모습
	while(i < prs_data->vert)
	{
		point_arr[i] = (t_point *)malloc(sizeof(t_point) * prs_data->horiz);
		if (point_arr[i] == 0)
			return (0);
		while(j < prs_data->horiz)
		{
			point_arr[i][j].x = i;
			point_arr[i][j].y = j;
			point_arr[i][j].z = z_atoi(&(point_arr[i][j]), &(splits[i][j][0]));
			j++;
		}
		j = 0;
		i++;
	}
	return (point_arr);
}
