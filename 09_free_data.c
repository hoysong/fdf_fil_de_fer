/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_free_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 01:51:25 by hoysong           #+#    #+#             */
/*   Updated: 2024/08/16 19:24:59 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"

void	free_splits(char ***splits)
{
	char	***tri_ptr;
	int		i;

	i = 0;
	tri_ptr = splits;
	while ((*splits))
	{
		while ((*splits)[i])
			free((*splits)[i++]);
		free((*splits)[i]);
		free(*splits);
		++splits;
		i = 0;
	}
	free(tri_ptr);
}

void	free_points(t_prs_data *prs_data)
{
	int		i;
	t_point	**point_arr;

	i = 0;
	point_arr = prs_data->point;
	while (i < prs_data->vert)
		free(point_arr[i++]);
	free(point_arr);
}

void	free_ivld_map(t_mlx_ptrs *mlx_ptrs)
{
	free_splits(mlx_ptrs->prs_data->splits);
	destroy_doubly_list(mlx_ptrs->prs_data->gnl_node);
	free(mlx_ptrs->prs_data);
}
