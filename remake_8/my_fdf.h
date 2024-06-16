/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 07:25:01 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/13 16:02:36 by hoysong          ###   ########.fr       */
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


static void	setup_call_atoi(int *second_index, int *x_elements, char ****free_splits, char ***splits);
int			map_vld_chk(char ***splits);

int			***gen_int_arr(int x_elements, int file_line_count);
void		free_splits(char ***splits);
int			***splits_to_int(char ***splits, int file_line_count);
int			***gen_int_arr(int x_elements, int file_line_count);
int			count_x_elements(char **splits_one_line);
void			hex_to_dec(char *num_str, int *height, int *color);
int			fdf_atoi(char **nptr);
char		***get_splits(int fd, int *file_line_count);

#endif
