/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 07:25:01 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/06 23:15:08 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FDFMLX_H
# define FDFMLX_H
# include "my_libft/linked_list/lkdlist.h"
# include <stdio.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"
# include "my_libft/linked_list/lkdlist.h"
# include "my_libft/libft.h"
# include <math.h>

typedef struct s_point
{
	int	x;
	int	y;
	int	*z;
	int	*color;
} t_point;

typedef struct s_parse_data
{
	int		vert;
	int		horiz;
	int		file_lines;
	char	***splits;
	int		***int_arr;
	t_dnode	*gnl_node;
	t_point	**point;
} t_prs_data;

typedef struct s_img_struct
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img_strc;

typedef struct s_mlx_prts
{
	void	*init_ptr;
	void	*win_ptr;
	int		gap;
	t_prs_data	*prs_data;
	t_img_strc	*img_data;
}			t_mlx_ptrs;

typedef struct s_move_point
{
	int	mv_x;
	int	mv_y;
}	t_mv;

t_prs_data	*get_parsed_data(int fd, t_prs_data *prs_data);

#endif
