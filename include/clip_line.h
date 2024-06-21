/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:55:35 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/21 12:14:33 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIP_LINE_H
# define CLIP_LINE_H

typedef int	t_outcode;

enum e_outcode
{
	INSIDE = 0,
	LEFT = 1,
	RIGHT = 2,
	BOTTOM = 4,
	TOP = 8
};

extern int	clip_line(int *x0, int *y0, int *x1, int *y1);

#endif /* CLIP_LINE_H */
