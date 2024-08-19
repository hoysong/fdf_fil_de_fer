/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_get_parsed_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:26:00 by hoysong           #+#    #+#             */
/*   Updated: 2024/08/19 17:54:04 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

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
	while (i < (prs_data->file_lines))
	{
		splits[i] = ft_split((char *)gnl_node->data, ' ');
		gnl_node = gnl_node->next_node;
		++i;
	}
	return (splits);
}

static t_dnode	*read_file_with_gnl(int fd, t_prs_data *prs_data)
{
	t_dnode	*node_head;
	t_dnode	*gnl_node;

	prs_data->file_lines = 0;
	gnl_node = init_dubl();
	node_head = gnl_node;
	while (1)
	{
		gnl_node = insert_data_dubl(gnl_node, get_next_line(fd));
		prs_data->file_lines ++;
		if (gnl_node->data == NULL)
			break ;
	}
	prs_data->file_lines --;
	prs_data->vert = prs_data->file_lines;
	return (node_head);
}

static int	get_one_line_elements(char ***splits)
{
	int	i;

	i = 0;
	while (splits[0][i] != 0)
		i++;
	return (i);
}

int	map_vld_chk(t_prs_data *prs_data)
{
	int			x;
	int			y;
	int			elmts;
	const char	***splits;

	y = 0;
	elmts = prs_data->horiz;
	splits = (const char ***)prs_data->splits;
	while (y < prs_data->file_lines)
	{
		x = 0;
		while (splits[y][x] != 0)
		{
			if (splits[y][x][0] == '\n')
			{
				return (1);
			}
			x++;
		}
		if (x != elmts)
			return (1);
		y++;
	}
	return (0);
}

t_prs_data	*get_parsed_data(int fd, t_prs_data *prs_data)
{
	prs_data = malloc(sizeof(t_prs_data));
	if (prs_data == NULL)
		return (0);
	prs_data->gnl_node = read_file_with_gnl(fd, prs_data);
	prs_data->splits = split_gnl_data(prs_data, prs_data->gnl_node);
	prs_data->horiz = get_one_line_elements(prs_data->splits);
	if (map_vld_chk(prs_data))
	{
		prs_data->point = 0;
		return (prs_data);
	}
	prs_data->point = splits_to_points(prs_data, prs_data->splits);
	return (prs_data);
}
