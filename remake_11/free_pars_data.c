/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pars_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 01:16:38 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/30 01:18:42 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"

void	free_parse_data(int ***data, int elements, int lines)
{
	int	thrd;
	int	scnd;
	int	frst;

	thrd = 0;
	frst = 0;
	scnd = 0;
	while (thrd < 3)
	{
		while (scnd < lines)
		{
			free(data[thrd][scnd]);
			scnd++;
		}
			free(data[thrd]);
			scnd = 0;
			thrd++;
	}
	free(data);
}

