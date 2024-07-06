/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsed_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:26:00 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/07 00:04:53 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"

//static char	**split_gnl_node(t_dnode *gnl_node)
//{
//	return ();
//}

static t_dnode *read_file_with_gnl(int fd, t_prs_data *prs_data)
{
	t_dnode	*node_head;
	t_dnode	*gnl_node;

	prs_data->file_lines = 0;
	gnl_node = init_dubl();
	node_head = gnl_node;
	while(1)
	{
		gnl_node = insert_data_dubl(gnl_node, get_next_line(fd));
		prs_data->file_lines ++;
		if (gnl_node->data == NULL)
			break ;
	}
	prs_data->file_lines --;
	printf("file_lines(gnl): %d\n", prs_data->file_lines);
	return (node_head);
}

t_prs_data	*get_parsed_data(int fd, t_prs_data *prs_data)
{
	prs_data = malloc(sizeof(t_prs_data));
	if (prs_data == NULL)
		return (0);
	prs_data->gnl_node = read_file_with_gnl(fd, prs_data);
	return (prs_data);
}
