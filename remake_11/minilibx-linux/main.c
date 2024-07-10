/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 03:30:54 by hoysong           #+#    #+#             */
/*   Updated: 2024/05/27 15:30:13 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "minilibx-linux/mlx.h"

/* img ptr's will used later */
//typedef struct s_img_ptr
//{
//} t_img_ptr;

typedef struct s_mlx_ptrs
{
	void	*init_ptr;
	void	*win_ptr;
} t_mlx_ptrs;

int	hdl_keys(int input, t_mlx_ptrs *mlx_ptrs)
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

int	main(void)
{
	t_mlx_ptrs mlx_ptrs;

	mlx_ptrs.init_ptr = mlx_init();
	mlx_ptrs.win_ptr = mlx_new_window(mlx_ptrs.init_ptr, 500, 500, "my_mlx_1");
	mlx_hook(mlx_ptrs.win_ptr, 2, 1L<<0, hdl_keys, &mlx_ptrs);

	mlx_loop(mlx_ptrs.init_ptr);
}
