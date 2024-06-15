/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@42gyeongsan.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:34:41 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/10 19:26:49 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

static char	***make_splits(t_dnode *gnl_head, int file_line_count)
{
	char	***splits;
	int		***parsedata;
	int		third_index;

	splits = (char ***)malloc(sizeof(char *) * (file_line_count + 1));
	if (splits == NULL)
		return (0);

	third_index = 0;

	gnl_head = gnl_head->next_node;
	splits[file_line_count] = NULL;

	while (third_index < file_line_count)
	{
		splits[third_index] = ft_split((char *)gnl_head->data, ' ');
		gnl_head = gnl_head->next_node;
		++third_index;
	}
	return (splits);
}

/* read with get_next_line and make linked_list */
static t_dnode *read_with_gnl(int fd, int *file_line_count)
{
	t_dnode	*gnl_node;
	t_dnode	*node_head;
	char	***splits;

	gnl_node = init_dubl();
	node_head = gnl_node;

	while (1)
	{
		gnl_node = insert_data_dubl(gnl_node, get_next_line(fd));
		(*file_line_count)++;
		if (gnl_node->data == NULL)
			break ;
	}
	(*file_line_count)--;
/* == debug_read_lkd_list's data == */
	printf("file's line: %d\n", (*file_line_count));
	printf("doubly_linked_list's data\n");
	t_dnode	*print_node;
	print_node = node_head;
	print_node = print_node->next_node;
	while (print_node->data != NULL)
	{
		printf("%s", (char *)print_node->data);
		print_node = print_node->next_node;
	}
	printf("\n");
/*============*/
	return (node_head);
}

/* make splits after make gnl linked list */
char	***get_splits(int fd, int *file_line_count)
{
	t_dnode	*gnl_node;
	char	***splits;

	gnl_node = read_with_gnl(fd, file_line_count);
	splits = make_splits(gnl_node, (*file_line_count));
	destroy_doubly_list(gnl_node);
	return (splits);
}
