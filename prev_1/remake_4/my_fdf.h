/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 07:25:01 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/09 18:05:14 by hoysong          ###   ########.fr       */
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
char		***read_file(int fd, int *file_line_count);
t_dnode		*get_parse_data(int fd);
void		free_splits(char ***splits);
int			***splits_to_int(char ***splits);

#endif
