/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_get_scale_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 07:56:42 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/24 05:52:00 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"

static void	get_bigst_data(t_prs_data *prs_data, t_mv *cdnate)
{
	t_point **point;
	int	i;
	int	j;

	i = 0;
	point = prs_data->point;
	while (i < prs_data->vert)
	{
		j = 0;
		while (j < prs_data->horiz)
		{
			if (cdnate->mv_x < point[i][j].x)
				cdnate->mv_x = point[i][j].x;
			if (cdnate->mv_y < point[i][j].y)
				cdnate->mv_y = point[i][j].y;
			j++;
		}
		i++;
	}
	printf("cdnate x; %d\n", cdnate->mv_x);
	printf("cdnate y; %d\n", cdnate->mv_y);
}

static void	calc_gap(t_prs_data *prs_data, t_mv *cdnate)
{
	if (cdnate->mv_x > 1000)
	{
		printf("new_gap x; %d\n", cdnate->mv_x);
		printf("new_gap y; %d\n", cdnate->mv_y);
	}
}

static void	apply_gap(t_prs_data *prs_data, t_mv *cdnate)
{
}

void	resize_scale(t_prs_data *prs_data)
{
	t_mv cdnate;

	cdnate.mv_x = 0;
	cdnate.mv_y = 0;
	get_bigst_data(prs_data, &(cdnate));
	printf("new_gap x; %d\n", cdnate.mv_x);
	printf("new_gap y; %d\n", cdnate.mv_y);
	calc_gap(prs_data, &(cdnate));
	apply_gap(prs_data, &(cdnate));
}
