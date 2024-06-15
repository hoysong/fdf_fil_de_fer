/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:34:41 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/09 09:47:02 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/X.h>
#include <X11/keysym.h>

#include "minilibx-linux/mlx.h"
#include "my_libft/linked_list/lkdlist.h"
#include "my_libft/libft.h"
#define OPEN_ERR		1
#define FILE_NAME_ERR	2
#define MAP_ERR			3

typedef struct s_list_1
{
	void	*init_ptr;
	void	*win_ptr;
	void	*data;
	t_dnode	*pars_data;
}			t_mlx_ptrs;

void	err_hdler(int err_num)
{
	if (err_num == OPEN_ERR)
	{
		write(1, "[err code: 1] OPEN_ERR\n", 23);
		exit(1);
	}
}

int	ft_atoi(const char *char_num)
{
	int	int_num;
	int	minus;

	int_num = 0;
	minus = 1;
	if (*char_num == '-')
	{
		minus = -1;
		char_num++;
	}
	while (*char_num && *char_num >= '0' && *char_num <= '9')
		int_num = int_num * 10 + *(char *)char_num++ - '0';
	int_num *= minus;
	return (int_num);
}

int	inpt_hdler(int input, t_mlx_ptrs *mlx_ptrs)
{
	printf("input: %d\n", input);
	if (input == XK_Escape)
	{
		mlx_destroy_window(mlx_ptrs->init_ptr, mlx_ptrs->win_ptr);
		mlx_destroy_display(mlx_ptrs->init_ptr);
		free(mlx_ptrs->init_ptr);
		exit(1);
	}
	return (0);
}

// ===============================================================================================================

void	free_splits(char ***splits)
{
	int		third_index;
	int		second_index;

	third_index = 0;
	second_index = 0;
	while (splits[third_index] != NULL)
	{
		printf("=== 3rd dim: %d ===\n", third_index);
		while (splits[third_index][second_index] != NULL)
		{
			printf("2nd dim[%d]: %s\n", second_index, splits[third_index][second_index]);
			free(splits[third_index][second_index]);
			++second_index;
		}
		printf("2nd dim[%d]: %s\n\n", second_index, splits[third_index][second_index]);
		second_index = 0;
		free(splits[third_index]);
		++third_index;
	}
	printf("3rd dim's last: %p\n", splits[third_index]);
	free(splits);
}

int	count_line_elements(char **splits_one_line)
{
	int	elements;

	elements = 0;
	// count unitl splits_one_line is not NULL
	// and go back 1 byte to check it is newlin
	while (*splits_one_line != NULL)
	{
		++elements;
		++splits_one_line;
	}
	return (elements);
}

static void	setup_call_atoi(int *second_index, int *x_elements, char ****free_splits, char ***splits)
{
	*second_index = 0;
	*free_splits = splits;
	*x_elements = count_line_elements((*splits));
}

//int	***gen_int_arr(int x_elements, int file_line_count)
//{
//	printf("gen int arr...\n");
//	int	***arr_3;
//	int	thr_dim;
//	int	sec_dim;
//
//	thr_dim = 0;
//	sec_dim = 0;
//	arr_3 = (int ***)malloc(sizeof(int *) * 3);
//	if (arr_3 == NULL)
//		return (0);
//	arr_3[2] = NULL;
//
//	arr_3[0] = malloc(sizeof(int *) * (file_line_count + 1));
//	if (arr_3[0] == NULL)
//		return (0);
//	arr_3[0][file_line_count] = NULL;
//
//	arr_3[1] = malloc(sizeof(int *) * (file_line_count + 1));
//	if (arr_3[1] == NULL)
//		return (0);
//	arr_3[1][file_line_count] = NULL;
//
//	return (arr_3);
//}

int	***gen_int_arr(int x_elements, int file_line_count)
{
	printf("gen int arr...\n");
	int	***arr_3;
	int	third;
	int	second;

	arr_3 = (int ***)malloc(sizeof(int **) * 3);
	arr_3[2] = NULL;
	third = 0;
	second = 0;
	while (arr_3[third] != NULL) // gen **arr
	{
		arr_3[third] = (int **)malloc(sizeof(int *) * (file_line_count + 1));
		if (arr_3[third] == NULL)
			return (0);
		arr_3[third][file_line_count] = NULL;
		while (arr_3[third][second])
		{
			arr_3[third][second] = (int *)malloc(sizeof(int) * (x_elements));
			if (arr_3[third][second] == NULL)
				return (0);
			second++;
		}
		third++;
	}
	return (arr_3);
}

int	***call_atoi(char ***splits, int file_line_count)
{
	char	***free_splits;
	int		***int_arr;
	int		second_index;
	int		x_elements;

	setup_call_atoi(&second_index, &x_elements, &free_splits,splits);
	int_arr = gen_int_arr(x_elements, file_line_count);
	while ((*splits) != NULL)
	{
		while ((*splits)[second_index] != NULL)
		{
			free((*splits)[second_index]);
			++second_index;
		}
		free((*splits));
		++splits;
		if ((second_index != x_elements) && (*splits) != NULL)
			printf("!!ivld_map_detected!!\n");
		second_index = 0;
	}
	free(free_splits);
	return (0);
}

char	***atoi_after_split(t_dnode *gnl_head, int file_line_count)
{
	char	***splits;
	int		***parsedata;
	int		third_index;

	splits = (char ***)malloc(sizeof(char *) * (file_line_count + 1));
	if (splits == NULL)
		return (0);

	third_index = 0;

	gnl_head = gnl_head->next_node;
	splits[file_line_count] = NULL; // init 3dim ptr's last addr.

	while (third_index < file_line_count)
	{
		splits[third_index] = ft_split((char *)gnl_head->data, ' ');
		gnl_head = gnl_head->next_node;
		++third_index;
	}
	call_atoi(splits, file_line_count);
	//free_splits(splits);
	return (splits);
}

t_dnode	*get_parsed_data(int fd)
{
	t_dnode	*gnl_node;
	t_dnode	*node_head;
	int		file_line_count;
	char	***splits;

	gnl_node = init_dubl();
	node_head = gnl_node;
	file_line_count = 0;

	while (1)
	{
		gnl_node = insert_data_dubl(gnl_node, get_next_line(fd));
		file_line_count++;
		if (gnl_node->data == NULL)
			break ;
	}
	file_line_count--;
/* == debug == */
	printf("file's line: %d\n", file_line_count);
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
	splits = atoi_after_split(node_head, file_line_count);
	//get_z_atoi();
	//get_colors();
	//get_colors_atoi();
	destroy_doubly_list(node_head);
	return (0);
}

int	main(int argc, char *argv[])
{
	int			fd;
	int			i;
	char		**str;
	t_mlx_ptrs	mlx_ptrs;

	i = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		err_hdler(OPEN_ERR);
	mlx_ptrs.init_ptr = mlx_init();
	if (mlx_ptrs.init_ptr == 0)
	{
		mlx_destroy_display(mlx_ptrs.init_ptr);
		free(mlx_ptrs.init_ptr);
	}
	mlx_ptrs.win_ptr = mlx_new_window(mlx_ptrs.init_ptr, 500, 500, "window_1");
	if (mlx_ptrs.win_ptr == 0)
	{
		mlx_destroy_window(mlx_ptrs.init_ptr, mlx_ptrs.win_ptr);
		mlx_destroy_display(mlx_ptrs.init_ptr);
		free(mlx_ptrs.init_ptr);
	}
	mlx_ptrs.pars_data = get_parsed_data(fd);
	mlx_hook(mlx_ptrs.win_ptr, KeyPress, KeyPressMask, inpt_hdler, &mlx_ptrs);
	mlx_loop(mlx_ptrs.init_ptr);
}
