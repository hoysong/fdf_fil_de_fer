/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@42gyeongsan.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:34:41 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/10 18:03:24 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_fdf.h"
#define OPEN_ERR		1
#define FILE_NAME_ERR	2
#define MAP_ERR			3

typedef struct s_list_1
{
	void	*init_ptr;
	void	*win_ptr;
	void	*data;
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

// ===================================================================================

void	err_hdler(int err_num)
{
	if (err_num == OPEN_ERR)
	{
		write(1, "[err code: 1] OPEN_ERR\n", 23);
		exit(1);
	}
}

t_mlx_ptrs	*get_parsed_data(int fd, t_mlx_ptrs *mlx_ptrs)
{
	char	***splits;
	int		file_line_count;
	int		map_chk_flg;

	file_line_count = 0;
	splits = read_file(fd, &file_line_count); // split with ft_split
	// splits_to_int(splits); // make int arr from splits
	map_chk_flg = map_vld_chk(splits); // free splits and map vld chk
	//if (map_vld_chk == 0)
	//	return (0);
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
	setup_main(&mlx_ptrs);
	mlx_ptrs.data = get_parsed_data(fd, &mlx_ptrs);
	mlx_hook(mlx_ptrs.win_ptr, KeyPress, KeyPressMask, inpt_hdler, &mlx_ptrs);
	mlx_loop(mlx_ptrs.init_ptr);
}
