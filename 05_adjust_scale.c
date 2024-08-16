/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_adjust_scale.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 07:56:42 by hoysong           #+#    #+#             */
/*   Updated: 2024/08/16 14:44:29 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"

static void	get_bigst_data(t_prs_data *prs_data, t_mv *cdnate)
{
	t_point	**point;
	int		i;
	int		j;

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
}

static double	calc_gap(t_mv *cdnate)
{
	double	new_gap;

	new_gap = 0.0;
	if (cdnate->mv_x - WIN_X > cdnate->mv_y - WIN_Y)
	{
		new_gap = cdnate->mv_x - WIN_X;
		new_gap = 1 - (new_gap / cdnate->mv_x);
	}
	else if (cdnate->mv_y - WIN_X < cdnate->mv_y - WIN_Y)
	{
		new_gap = cdnate->mv_y - WIN_Y;
		new_gap = 1 - (new_gap / cdnate->mv_y);
	}
	return (new_gap);
}

static void	apply_gap(t_prs_data *prs_data, double new_gap)
{
	int		i;
	int		j;
	t_point	**point;

	i = 0;
	j = 0;
	point = prs_data->point;
	while (i < prs_data->vert)
	{
		j = 0;
		while (j < prs_data->horiz)
		{
			point[i][j].x *= (new_gap);
			point[i][j].y *= (new_gap);
			j++;
		}
		i++;
	}
}

void	adjust_scale(t_prs_data *prs_data)
{
	t_mv	cdnate;
	double	new_gap;

	cdnate.mv_x = 0;
	cdnate.mv_y = 0;
	get_bigst_data(prs_data, &(cdnate));
	if (cdnate.mv_x < WIN_X && cdnate.mv_y < WIN_Y)
		return ;
	new_gap = calc_gap(&(cdnate));
	apply_gap(prs_data, new_gap);
}
