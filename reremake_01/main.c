/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@42gyeongsan.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:34:41 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/07 12:27:56 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"
#define OPEN_ERR		1
#define FILE_NAME_ERR	2
#define IVLD_MAP		3

int	inpt_hdler(int input, t_mlx_ptrs *mlx_ptrs)
{
	printf("input: %d\n", input);
	if (input == XK_Escape)
	{
		mlx_destroy_window(mlx_ptrs->init_ptr, mlx_ptrs->win_ptr);
		mlx_destroy_display(mlx_ptrs->init_ptr);
		destroy_doubly_list(mlx_ptrs->prs_data->gnl_node);
		free(mlx_ptrs->prs_data);
		free(mlx_ptrs->init_ptr);
		exit(1);
	}
	return (0);
}

static void	setup_mlx(t_mlx_ptrs *mlx_ptrs)
{
	t_img_strc	*img_strc;

//	img_strc = malloc(sizeof(t_img_strc));
	mlx_ptrs->gap = 10;
	/* === init_mlx === */
	mlx_ptrs->init_ptr = mlx_init();
	if (mlx_ptrs->init_ptr == 0)
	{
		mlx_destroy_display(mlx_ptrs->init_ptr);
		free(mlx_ptrs->init_ptr);
	}
	/* === gen win ptr === */
	mlx_ptrs->win_ptr = mlx_new_window(mlx_ptrs->init_ptr, 1000, 1000, "window_1");
	if (mlx_ptrs->win_ptr == 0)
	{
		mlx_destroy_window(mlx_ptrs->init_ptr, mlx_ptrs->win_ptr);
		mlx_destroy_display(mlx_ptrs->init_ptr);
		free(mlx_ptrs->init_ptr);
	}
}

// =================================================================================

void	err_hdler(int err_num, t_mlx_ptrs *mlx_ptrs)
{
	if (err_num == OPEN_ERR)
	{
		write(1, "[err code: 1] open_err\n", 23);
		exit(1);
	}
	else if (err_num == IVLD_MAP)
	{
		free(mlx_ptrs->prs_data);
		write(1, "[err code: 3] ivld_map\n", 23);
		exit(1);
	}
}

int	main(int argc, char *argv[])
{
	int			fd;
	char		**str;
	t_mlx_ptrs	mlx_ptrs;

	if (argc <= 1)
		err_hdler(OPEN_ERR, 0);
	fd = open(argv[1], O_RDONLY);
	mlx_ptrs.prs_data = get_parsed_data(fd, mlx_ptrs.prs_data);
	setup_mlx(&mlx_ptrs);
	mlx_hook(mlx_ptrs.win_ptr, KeyPress, KeyPressMask, inpt_hdler, &mlx_ptrs);
	mlx_loop(mlx_ptrs.init_ptr);
}
