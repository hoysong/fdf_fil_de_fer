/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:34:41 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/07 17:08:43 by hoysong          ###   ########.fr       */
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

void	err_hdler(int err_num)
{
	if (err_num == OPEN_ERR)
	{
		write(1, "[err code: 1] OPEN_ERR\n", 23);
		exit(1);
	}
}

char	***get_space_splits(t_dnode *gnl_head, int file_line_count)
{
	char	***splits;
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

	return (splits);
}

//char	***get_comma_splits(char ***spc_splits)
//{
//	char	;
//}

//int	map_vld_chk(char ***splits);
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

t_dnode	*get_parse_data(int fd)
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
	splits = get_space_splits(node_head, file_line_count);
	//get_comma_splits();
	free_splits(splits);
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
	mlx_ptrs.pars_data = get_parse_data(fd);
	mlx_hook(mlx_ptrs.win_ptr, KeyPress, KeyPressMask, inpt_hdler, &mlx_ptrs);
	mlx_loop(mlx_ptrs.init_ptr);
}
