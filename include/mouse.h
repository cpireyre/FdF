/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copireyr <copireyr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:10:45 by copireyr          #+#    #+#             */
/*   Updated: 2024/08/09 16:25:27 by copireyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOUSE_H
# define MOUSE_H

# include "render.h"

extern void	mouse_hooks_set(t_render_context *ctx);
extern void drag(t_render_context *ctx);

#endif /* MOUSE_H */
