/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:34:41 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/04 18:14:35 by hoysong          ###   ########.fr       */
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
	t_dnode	*gnl_node;
}			t_mlx_ptrs;

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

char	***get_splits(t_dnode *node_head, int file_line_count)
{
	char	***splits;

	splits = ft_calloc(file_line_count + 1, sizeof(char *));
	while (file_line_count)
	{
		*splits = ft_split(node_head->data, ' ');
		splits++;
		node_head = node_head->next_node;
		file_line_count--;
	}
	return (splits);
}

void	free_parsed(char ***parsed)
{
	char	***ptr;
	ptr = parsed;
	(*ptr)
	free();
}

t_dnode	*parse_file(int fd)
{
	t_dnode	*gnl_node;
	t_dnode	*node_head;
	int		file_line_count;
	char	***parsed;

	gnl_node = init_dubl();
	node_head = gnl_node;
	file_line_count = 0;
	while (1)
	{
		gnl_node = insert_data_dubl(gnl_node, get_next_line(fd));
//		gnl_node->next_node = init_dubl();
//		gnl_node->next_node->data = get_next_line(fd);
//		gnl_node->next_node->prev_node = gnl_node;
//		gnl_node = gnl_node->next_node;
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
/*============*/
	parsed = get_splits(node_head, file_line_count);
	free_parsed(parsed);
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
	mlx_ptrs.gnl_node = parse_file(fd);
	mlx_hook(mlx_ptrs.win_ptr, KeyPress, KeyPressMask, inpt_hdler, &mlx_ptrs);
	mlx_loop(mlx_ptrs.init_ptr);
}
