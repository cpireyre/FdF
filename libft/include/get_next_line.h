/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:52:30 by copireyr          #+#    #+#             */
/*   Updated: 2024/05/20 10:14:21 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	500
# endif

#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strcat(char *dst, const char *src);
char	*ft_strndup(const char *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);

#endif
