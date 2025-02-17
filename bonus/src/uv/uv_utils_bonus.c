/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:32:17 by likong            #+#    #+#             */
/*   Updated: 2025/02/17 15:43:55 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static void	set_rotate_value(t_shape *shape, int axis, double angle)
{
	shape->u_axis = vector_rotate(shape->u_axis, axis, angle);
	shape->v_axis = vector_rotate(shape->v_axis, axis, angle);
}

void	rotate_uv(t_key *keys, t_shape *shape)
{
	if (keys->key[I])
		set_rotate_value(shape, X, ROTATE);
	else if (keys->key[K])
		set_rotate_value(shape, X, (-ROTATE));
	else if (keys->key[J])
		set_rotate_value(shape, Y, ROTATE);
	else if (keys->key[L])
		set_rotate_value(shape, Y, (-ROTATE));
	else if (keys->key[U])
		set_rotate_value(shape, Z, ROTATE);
	else if (keys->key[O])
		set_rotate_value(shape, Z, (-ROTATE));
}

t_color	get_pixel(t_image img, int x, int y)
{
	uint8_t	*start;
	t_color	color;

	start = (uint8_t *)(img.data + (y * img.size_line) + (x * (img.bpp / 8)));
	color.red = (start[2]);
	color.green = (start[1]);
	color.blue = (start[0]);
	return (color);
}
