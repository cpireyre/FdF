/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:53:59 by copireyr          #+#    #+#             */
/*   Updated: 2024/08/05 11:38:29 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "arena.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1024
# endif /* BUFFER_SIZE */

typedef struct s_gnl_list
{
	char				chunk[BUFFER_SIZE];
	int					size;
	int					newline_index;
	struct s_gnl_list	*next;
}				t_gnl_list;

extern char	*get_next_line(int fd);
extern char	*arena_gnl(t_arena arena, int fd);

void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_calloc(size_t elems, size_t elem_size);

#endif /* GET_NEXT_LINE_H */
