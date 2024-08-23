/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <hoysong@42gyeongsan.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:34:41 by hoysong           #+#    #+#             */
/*   Updated: 2024/08/23 20:16:26 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "my_fdf.h"

static int	inpt_hdler(int input, t_mlx_ptrs *mlx_ptrs)
{
	if (input == XK_Escape)
	{
		mlx_destroy_image(mlx_ptrs->init_ptr, mlx_ptrs->img_data->img_ptr);
		mlx_destroy_window(mlx_ptrs->init_ptr, mlx_ptrs->win_ptr);
		mlx_destroy_display(mlx_ptrs->init_ptr);
		destroy_doubly_list(mlx_ptrs->prs_data->gnl_node);
		free_splits(mlx_ptrs->prs_data->splits);
		free_points(mlx_ptrs->prs_data);
		free(mlx_ptrs->prs_data);
		free(mlx_ptrs->init_ptr);
		free(mlx_ptrs->img_data);
		exit(1);
	}
	return (0);
}

static void	setup_mlx(t_mlx_ptrs *mlx_ptrs)
{
	t_img_strc	*img;

	img = malloc(sizeof(t_img_strc));
	mlx_ptrs->init_ptr = mlx_init();
	if (mlx_ptrs->init_ptr == 0)
	{
		mlx_destroy_display(mlx_ptrs->init_ptr);
		free(mlx_ptrs->init_ptr);
	}
	mlx_ptrs->win_ptr = mlx_new_window(mlx_ptrs->init_ptr, WIN_X, WIN_Y, "fdf");
	if (mlx_ptrs->win_ptr == 0)
	{
		mlx_destroy_window(mlx_ptrs->init_ptr, mlx_ptrs->win_ptr);
		mlx_destroy_display(mlx_ptrs->init_ptr);
		free(mlx_ptrs->init_ptr);
	}
	img->img_ptr = mlx_new_image(mlx_ptrs->init_ptr, 1920, 1010);
	img->addr = mlx_get_data_addr(
			img->img_ptr, &img->bits_per_pixel, &img->size_line, &img->endian);
	mlx_ptrs->img_data = img;
}

void	err_hdler(int err_num, t_mlx_ptrs *mlx_ptrs)
{
	if (err_num == NO_FILE)
		ft_putstr_fd("[err] no_file\n", 1);
	else if (err_num == TOO_MANY_FILES)
		ft_putstr_fd("[err] too many files\n", 1);
	else if (err_num == IVLD_FORMAT)
		ft_putstr_fd("[err] check file's format\n", 1);
	else if (err_num == OPEN_ERR)
	{
		ft_putstr_fd("[err] open fail\n", 1);
	}
	else if (err_num == IVLD_MAP)
	{
		ft_putstr_fd("[err] ivld_map\n", 1);
		free_ivld_map(mlx_ptrs);
	}
	exit(1);
}

static int	fmt_chk(char *file_name)
{
	int	i;

	i = 0;
	while (file_name[i])
		i++;
	if (i < 4)
		return (1);
	if (file_name[i - 1] == 'f'
		&& file_name[i - 2] == 'd'
		&& file_name[i - 3] == 'f'
		&& file_name[i - 4] == '.')
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	int			fd;
	t_mlx_ptrs	mlx_ptrs;

	if (argc <= 1)
		err_hdler(NO_FILE, 0);
	else if (argc > 2)
		err_hdler(TOO_MANY_FILES, 0);
	if (fmt_chk(argv[1]))
		err_hdler(IVLD_FORMAT, 0);
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		err_hdler(OPEN_ERR, 0);
	mlx_ptrs.prs_data = get_parsed_data(fd, mlx_ptrs.prs_data);
	if (mlx_ptrs.prs_data->point == 0)
		err_hdler(IVLD_MAP, &mlx_ptrs);
	setup_mlx(&mlx_ptrs);
	iso_prjc(mlx_ptrs.img_data, mlx_ptrs.prs_data);
	adjust_scale(mlx_ptrs.prs_data);
//	adjust_scale(mlx_ptrs.prs_data);
	draw_line(mlx_ptrs.img_data, mlx_ptrs.prs_data);
	mlx_hook(mlx_ptrs.win_ptr, KeyPress, KeyPressMask, inpt_hdler, &mlx_ptrs);
	mlx_put_image_to_window(mlx_ptrs.init_ptr,
		mlx_ptrs.win_ptr, mlx_ptrs.img_data->img_ptr, 0, 0);
	mlx_loop(mlx_ptrs.init_ptr);
}
