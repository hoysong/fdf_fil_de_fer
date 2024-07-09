/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsed_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:26:00 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/10 02:14:27 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

//static void	to_upper(char *char_ptr)
//{
//	if (*char_ptr <= 'z' && *char_ptr >= 'a')
//		*char_ptr -= 32;
//}

static char	***split_gnl_data(t_prs_data *prs_data, t_dnode *gnl_node)
{
	int		i;
	char	***splits;

	splits = (char ***)malloc(sizeof(char **) * (prs_data->file_lines + 1));
	if (splits == 0)
		return (0);
	splits[prs_data->file_lines] = NULL;
	i = 0;
	gnl_node = gnl_node->next_node;
	while(i < (prs_data->file_lines))
	{
		splits[i] = ft_split((char *)gnl_node->data, ' ');
		gnl_node = gnl_node->next_node;
		//printf("%s\n", *(splits[i]));
		++i;
	}
//	printf("make splits: %d\n", i);
	return (splits);
}

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
	prs_data->vert = prs_data->file_lines;
//	printf("file_lines(gnl): %d\n", prs_data->file_lines);
	return (node_head);
}

static int	get_one_line_elements(char ***splits)
{
	int	i;
	i = 0;
	while(splits[0][i] != 0)
		i++;
	return (i);
}


t_prs_data	*get_parsed_data(int fd, t_prs_data *prs_data)
{
	prs_data = malloc(sizeof(t_prs_data));
	if (prs_data == NULL)
		return (0);
	prs_data->gnl_node = read_file_with_gnl(fd, prs_data);
	prs_data->splits = split_gnl_data(prs_data, prs_data->gnl_node);
	prs_data->horiz = get_one_line_elements(prs_data->splits);
	prs_data->point = splits_to_points(prs_data, prs_data->splits);
	int	i = 0;
	int	j = 0;
//	while(i < prs_data->vert)
//	{
//		printf("%d\n", i);
//		while(j < prs_data->horiz)
//		{
//			printf("%3d, ", prs_data->point[i][j].z);
//			printf("%.3d", prs_data->point[i][j].color);
//			j++;
//		}
//		printf("\n");
//		i++;
//		j = 0;
//	}
	return (prs_data);
}
