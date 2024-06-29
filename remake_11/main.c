/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@42gyeongsan.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:34:41 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/30 01:45:41 by hoysong          ###   ########.fr       */
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
	debug_point_arr(mlx_ptrs);
		mlx_destroy_image(mlx_ptrs->init_ptr, (mlx_ptrs->img_data)->img_ptr);
		mlx_destroy_window(mlx_ptrs->init_ptr, mlx_ptrs->win_ptr);
		mlx_destroy_display(mlx_ptrs->init_ptr);
//		free_point_arr(mlx_ptrs);
		free_parse_data(mlx_ptrs->data->int_arr, mlx_ptrs->data->horiz, mlx_ptrs->data->vert);
		free(mlx_ptrs->data);
		free(mlx_ptrs->img_data);
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
	t_img_strc	*img_strc;

	img_strc = malloc(sizeof(t_img_strc));
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
	/* == new_image ==*/
//	printf("addr: %p\n", img_strc->addr);
	img_strc->img_ptr = mlx_new_image(mlx_ptrs->init_ptr, 500, 500);
	img_strc->addr = mlx_get_data_addr(img_strc->img_ptr, &img_strc->bits_per_pixel, &img_strc->size_line, &(img_strc->endian));
	printf("%d\n", img_strc->endian);
	printf("addr: %p\n", img_strc->addr);
	mlx_ptrs->img_data = img_strc;
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
	debug_splits(prs_data->splits);
	prs_data->horiz = count_x_elements((*prs_data->splits));
	/*=== debug ===*/
	printf("vert elements: %d\n", prs_data->horiz);
	printf("hriz elements: %d\n", prs_data->vert);
	prs_data->int_arr = splits_to_int(prs_data->splits, prs_data->horiz, prs_data->vert);
	mlx_ptrs->data = prs_data;
	mlx_ptrs->data->point = int_to_point(mlx_ptrs);
	debug_parsed_data(prs_data->int_arr, prs_data->horiz, prs_data->vert);
	return (prs_data);
}

int	main(int argc, char *argv[])
{
	int			fd;
	char		**str;
	t_mlx_ptrs	mlx_ptrs;

	if (argc <= 1)
		err_hdler(OPEN_ERR, 0);
	fd = open(argv[1], O_RDONLY);
	mlx_ptrs.data = get_parsed_data(fd, &mlx_ptrs);
	if (map_vld_chk((mlx_ptrs.data)->splits) == 0)
		err_hdler(IVLD_MAP, &mlx_ptrs);
	setup_mlx(&mlx_ptrs);
	mlx_hook(mlx_ptrs.win_ptr, KeyPress, KeyPressMask, inpt_hdler, &mlx_ptrs);

	int			i;
	i = 0;
//	while (i < 500)
//	{
//		my_mlx_pixel_put(&mlx_ptrs, i, 100, 0xffffff);
//		i++;
//	}
	make_trigon(&mlx_ptrs);
	mlx_put_image_to_window(mlx_ptrs.init_ptr, mlx_ptrs.win_ptr, mlx_ptrs.img_data->img_ptr, 100, 100);
	mlx_loop(mlx_ptrs.init_ptr);
}
