/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsed_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:26:00 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/09 04:31:47 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

//static void	to_upper(char *char_ptr)
//{
//	if (*char_ptr <= 'z' && *char_ptr >= 'a')
//		*char_ptr -= 32;
//}

static int	color_atoi(char *src)
{
	int	int_value;

	int_value = 0;
	if (*src == ',')
		src++;
	if (*src == '0' && *(src + 1) == 'x')
		src = src + 2;
	while (*src)
	{
		if ('0' <= *src && *src <= '9')
			int_value = (int_value * 16) + (*src - '0');
		if ('A' <= *src && *src <= 'F')
			int_value = (int_value * 16) + (*src - 55);
		++src;
	}
	if (int_value == 0)
		return (0xFFFFFF);
	else
		return (int_value);
	return (0);
}

static int	z_atoi(char *z)
{
	int	z_value;

	z_value = 0;
	while (*z && *z != ',' && *z != '\n')
	{
		z_value = (z_value * 10) + (*z - '0');
		z++;
	}
	return (z_value);
}

static t_point	**splits_to_points(t_prs_data *prs_data, char ***splits)
{
	t_point	**point_arr;

	point_arr = (t_point **)malloc(sizeof(t_point *) * prs_data->file_lines);
	if(point_arr == 0)
		return (0);
	return (point_arr);
	point_arr[0][0].z = z_atoi(&(splits[0][0][0]));
	point_arr[0][0].color = color_atoi(&(splits[0][0][0]));
}

static void	free_splits(char ***splits)
{
	char ***tri_ptr;
	int	i;

	i = 0;
	tri_ptr = splits;
	while ((*splits))
	{
		while ((*splits)[i])
		{
			free((*splits)[i]);
			++i;
		}
		free((*splits)[i]);
		free(*splits);
		++splits;
		i = 0;
	}
	free(tri_ptr);
}

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
		printf("%s\n", *(splits[i]));
		++i;
	}
	printf("make splits: %d\n", i);
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
	printf("file_lines(gnl): %d\n", prs_data->file_lines);
	return (node_head);
}

t_prs_data	*get_parsed_data(int fd, t_prs_data *prs_data)
{
	prs_data = malloc(sizeof(t_prs_data));
	if (prs_data == NULL)
		return (0);
	prs_data->gnl_node = read_file_with_gnl(fd, prs_data);
	prs_data->splits = split_gnl_data(prs_data, prs_data->gnl_node);
	free_splits(prs_data->splits);
	//splits_to_points();
	return (prs_data);
}
