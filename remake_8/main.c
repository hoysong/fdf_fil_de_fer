/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@42gyeongsan.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:34:41 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/13 16:04:16 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"
#define OPEN_ERR		1
#define FILE_NAME_ERR	2
#define IVLD_MAP		3

typedef struct s_list_1
{
	void	*init_ptr;
	void	*win_ptr;
	void	*data;
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

static void	setup_main(t_mlx_ptrs *mlx_ptrs)
{
	mlx_ptrs->init_ptr = mlx_init();
	if (mlx_ptrs->init_ptr == 0)
	{
		mlx_destroy_display(mlx_ptrs->init_ptr);
		free(mlx_ptrs->init_ptr);
	}
	mlx_ptrs->win_ptr = mlx_new_window(mlx_ptrs->init_ptr, 500, 500, "window_1");
	if (mlx_ptrs->win_ptr == 0)
	{
		mlx_destroy_window(mlx_ptrs->init_ptr, mlx_ptrs->win_ptr);
		mlx_destroy_display(mlx_ptrs->init_ptr);
		free(mlx_ptrs->init_ptr);
	}
}

// ===================================================================================

void	err_hdler(int err_num, t_mlx_ptrs *mlx_ptrs)
{
	if (err_num == OPEN_ERR)
	{
		write(1, "[err code: 1] open_err\n", 23);
		exit(1);
	}
	else if (err_num == IVLD_MAP)
	{
		write(1, "[err code: 3] ivld_map\n", 23);
		mlx_destroy_window(mlx_ptrs->init_ptr, mlx_ptrs->win_ptr);
		mlx_destroy_display(mlx_ptrs->init_ptr);
		free(mlx_ptrs->init_ptr);
		exit(1);
	}
}

t_mlx_ptrs	*get_parsed_data(int fd, t_mlx_ptrs *mlx_ptrs)
{
	char	***splits;
	int		***parsed_data;
	int		file_line_count;
	int		x_elements;

	file_line_count = 0;
	splits = get_splits(fd, &file_line_count); // split with ft_split
	parsed_data = splits_to_int(splits, file_line_count);
//	free_prs_data;
	if (map_vld_chk(splits) == 0)
		err_hdler(IVLD_MAP, mlx_ptrs);
	return (0);
}

int	main(int argc, char *argv[])
{
	int			fd;
	int			i;
	char		**str;
	t_mlx_ptrs	mlx_ptrs;

	i = 0;
	if (argc <= 1)
		err_hdler(OPEN_ERR, 0);
	fd = open(argv[1], O_RDONLY);

	setup_main(&mlx_ptrs);

	mlx_ptrs.data = 0;
	mlx_ptrs.data = get_parsed_data(fd, &mlx_ptrs);
	mlx_hook(mlx_ptrs.win_ptr, KeyPress, KeyPressMask, inpt_hdler, &mlx_ptrs);
	mlx_loop(mlx_ptrs.init_ptr);
}
