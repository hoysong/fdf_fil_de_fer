/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 07:25:01 by hoysong           #+#    #+#             */
/*   Updated: 2024/07/03 06:58:42 by hoysong          ###   ########.fr       */
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

typedef struct s_point
{
	int	x;
	int	y;
	int	*z;
	int	*color;
} t_point;

typedef struct s_parse_info
{
	int		vert;
	int		horiz;
	int 	height;
	char	***splits;
	int		***int_arr;
	t_point	**point;
} t_prs_info;

typedef struct s_img_struct
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img_strc;

typedef struct s_mlx_struct
{
	void	*init_ptr;
	void	*win_ptr;
	int		gap;
	t_prs_info	*data;
	t_img_strc	*img_data;
}			t_mlx_ptrs;

static void	setup_call_atoi(int *second_index, int *x_elements, char ****free_splits, char ***splits);
int			map_vld_chk(char ***splits);

int			***gen_int_arr(int x_elements, int file_line_count);
void		free_splits(char ***splits);
int			***splits_to_int(char ***splits, int x_elements, int file_line_count);
int			***gen_int_arr(int x_elements, int file_line_count);
int			count_x_elements(char **splits_one_line);
void			hex_to_dec(char *num_str, int *height, int *color);
int			fdf_atoi(char **nptr);
char		***get_splits(int fd, int *file_line_count);
void	free_parse_data(int ***data, int elements, int lines);

void	debug_splits(char ***splits);
void	debug_lkd_list(t_dnode *gnl_node);
void debug_parsed_data(int ***parsed_data, int elements, int lines);
void	debug_point_arr(t_mlx_ptrs *mlx_ptrs);
//void	put_image(int x, int y, t_mlx_ptrs *l, int color);
void  my_mlx_pixel_put(t_mlx_ptrs *data, int x, int y, int color);
//void	qter_view(int point_x, int point_y, t_mlx_ptrs *mlx_ptrs);
void	make_trigon(t_mlx_ptrs *mlx_ptrs);
void	int_to_point(t_mlx_ptrs *mlx_ptrs);
void	free_point_arr(t_mlx_ptrs *mlx_ptrs);

#endif
