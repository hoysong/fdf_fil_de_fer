/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsed_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:26:00 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/06 20:27:59 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"

static t_dnode *read_file_with_gnl(int fd)
{
	t_dnode	*node_head;
	t_dnode	*gnl_node;
	int file_line_count;

	file_line_count = 0;
	gnl_node = init_dubl();
	node_head = gnl_node;
	while(1)
	{
		gnl_node = insert_data_dubl(gnl_node, get_next_line(fd));
		file_line_count ++;
		if (gnl_node->data == NULL)
			break ;
	}
	file_line_count--;
	return (node_head);
}

t_prs_data	*get_parsed_data(int fd, t_prs_data *prs_data)
{
	prs_data = malloc(sizeof(t_prs_data));
	if (prs_data == NULL)
		return (0);
	t_dnode	*gnlgnl;
	prs_data->gnl_node = read_file_with_gnl(fd);
	return (prs_data);
}
