/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_get_scale_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 07:56:42 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/23 13:43:50 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"

static t_mv	*get_bigst_data(t_prs_data *prs_data)
{
	t_mv *cdnate;
	t_point **point;
	int	i;
	int	j;

	i = 0;
	point = prs_data->point;
	cdnate->mv_x = 0;
	cdnate->mv_y = 0;
	cdnate = (t_mv *)malloc(sizeof(t_mv));
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
	return (cdnate);
}

void	resize_scale(t_prs_data *prs_data)
{
	t_mv *cdnate;
	cdnate = get_bigst_data(prs_data);
}
