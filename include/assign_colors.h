/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_colors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:06:23 by copireyr          #+#    #+#             */
/*   Updated: 2024/06/21 11:12:25 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSIGN_COLORS_H
# define ASSIGN_COLORS_H

#include "t_map.h"
#include "interpolate_color.h"

extern void	assign_colors(t_map *map, uint32_t low_color, uint32_t high_color);

#endif /* ASSIGN_COLORS_H */
