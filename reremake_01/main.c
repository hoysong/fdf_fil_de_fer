/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:48:18 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/05 19:49:19 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_mlx_ptrs
{
}	t_mlx_ptrs;
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

	make_trigon(&mlx_ptrs);
	debug_point_arr(&mlx_ptrs);
	mlx_put_image_to_window(mlx_ptrs.init_ptr, mlx_ptrs.win_ptr, mlx_ptrs.img_data->img_ptr, 0, 0);
	mlx_loop(mlx_ptrs.init_ptr);
}
