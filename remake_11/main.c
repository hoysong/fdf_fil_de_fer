/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@42gyeongsan.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:34:41 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/23 01:29:59 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"
#define OPEN_ERR		1
#define FILE_NAME_ERR	2
#define IVLD_MAP		3

typedef struct s_img_struct
{
	void	*img_ptr;
	int		bits_ptr_pixel;
	int		size_line;
	int		endian;
}	t_img_strc;

typedef struct s_mlx_struct
{
	void	*init_ptr;
	void	*win_ptr;
	t_prs_info	*data;
	t_img_strc	*img_data;
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

//static void get_win_size(s_parse_info *prs_data, int *vert, int *horiz)
//{
//}

static void	setup_mlx(t_mlx_ptrs *mlx_ptrs)
{
	/* === init_mlx === */
	mlx_ptrs->init_ptr = mlx_init();
	if (mlx_ptrs->init_ptr == 0)
	{
		mlx_destroy_display(mlx_ptrs->init_ptr);
		free(mlx_ptrs->init_ptr);
	}
	/* === gen win ptr === */
	mlx_ptrs->win_ptr = mlx_new_window(mlx_ptrs->init_ptr, 500, 500, "window_1");
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
		free_parse_data(mlx_ptrs->data->int_arr, mlx_ptrs->data->horiz, mlx_ptrs->data->vert);
		free(mlx_ptrs->data);
		write(1, "[err code: 3] ivld_map\n", 23);
//		mlx_destroy_window(mlx_ptrs->init_ptr, mlx_ptrs->win_ptr);
//		mlx_destroy_display(mlx_ptrs->init_ptr);
//		free(mlx_ptrs->init_ptr);
		exit(1);
	}
}

t_prs_info	*get_parsed_data(int fd, t_mlx_ptrs *mlx_ptrs)
{
	t_prs_info	*prs_data;

	prs_data = malloc(sizeof(t_prs_info));
	if (prs_data == 0)
		return (0);
	prs_data->vert = 0;
	prs_data->splits = get_splits(fd, &prs_data->vert); // split with ft_split
//	debug_splits(prs_data->splits);
	prs_data->horiz = count_x_elements((*prs_data->splits));
	/*=== debug ===*/
	printf("vert elements: %d\n", prs_data->horiz);
	printf("hriz elements: %d\n", prs_data->vert);
	prs_data->int_arr = splits_to_int(prs_data->splits, prs_data->horiz, prs_data->vert);
//	debug_parsed_data(prs_data->int_arr, prs_data->horiz, prs_data->vert);
	return (prs_data);
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
	mlx_ptrs.data = get_parsed_data(fd, &mlx_ptrs);
	if (map_vld_chk((mlx_ptrs.data)->splits) == 0)
		err_hdler(IVLD_MAP, &mlx_ptrs);
	free_parse_data(mlx_ptrs.data->int_arr, mlx_ptrs.data->horiz, mlx_ptrs.data->vert);
	free(mlx_ptrs.data);
	setup_mlx(&mlx_ptrs);
	mlx_hook(mlx_ptrs.win_ptr, KeyPress, KeyPressMask, inpt_hdler, &mlx_ptrs);
	mlx_loop(mlx_ptrs.init_ptr);
}
