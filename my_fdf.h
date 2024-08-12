/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 07:25:01 by hoysong           #+#    #+#             */
/*   Updated: 2024/08/13 01:48:40 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_FDF_H
# define MY_FDF_H
# define WIN_X 1000
# define WIN_Y 800
# define NO_FILE 1
# define IVLD_FORMAT 2
# define IVLD_MAP 3
# define TOO_MANY_FILES 4
# include "src_files/linked_list/lkdlist.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"
# include "src_files/my_libft/libft.h"
# include <math.h>

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_parse_data
{
	int		vert;
	int		horiz;
	int		file_lines;
	char	***splits;
	t_dnode	*gnl_node;
	t_point	**point;
}	t_prs_data;

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
	void		*init_ptr;
	void		*win_ptr;
	int			gap;
	t_prs_data	*prs_data;
	t_img_strc	*img_data;
}			t_mlx_ptrs;

typedef struct s_move_point
{
	int	mv_x;
	int	mv_y;
}	t_mv;

typedef struct s_brzm
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	p;
	int	i_val;
}	t_brzm;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

t_prs_data	*get_parsed_data(int fd, t_prs_data *prs_data);
t_point		**splits_to_points(t_prs_data *prs_data, char ***splits);
void		free_splits(char ***splits);
void		free_points(t_prs_data *prs_data);
void		iso_prjc(t_img_strc *img_data, t_prs_data *prs_data);
void		my_mlx_pixel_put(t_img_strc *img_data, int x, int y, int color);
void		draw_line(t_img_strc *img_data, t_prs_data *prs_data);
void		db_point(t_mlx_ptrs *mlx_ptrs);
void		db_point_xy(t_mlx_ptrs *mlx_ptrs);
void		db_point_xy_prs_data(t_prs_data *prs_data);
void		pixel_test(t_img_strc *img_data, t_prs_data *prs_data);
void		adjust_scale(t_prs_data *prs_data);
void	put_pixel(t_brzm brzm, t_point start, t_point end, t_img_strc *img_data);
int	get_new_rgb(t_color *start, t_color *end, float precent);

#endif
