/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdfmlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoysong <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 07:25:01 by hoysong           #+#    #+#             */
/*   Updated: 2024/06/06 15:07:31 by hoysong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FDFMLX_H
# define FDFMLX_H

char    ***get_splits(t_dnode *node_head, int file_line_count);
t_dnode	*get_parse_data(int fd);

#endif
