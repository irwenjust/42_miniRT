/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:32:17 by likong            #+#    #+#             */
/*   Updated: 2025/02/17 13:33:03 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	rotate_uv(t_key *keys, t_shape *shape)
{
	if (keys->key[I])
	{
		shape->u_axis = vector_rotate(shape->u_axis, X, ROTATE);
		shape->v_axis = vector_rotate(shape->v_axis, X, ROTATE);
	}
	else if (keys->key[K])
	{
		shape->u_axis = vector_rotate(shape->u_axis, X, (-ROTATE));
		shape->v_axis = vector_rotate(shape->v_axis, X, (-ROTATE));
	}
	else if (keys->key[J])
	{
		shape->u_axis = vector_rotate(shape->u_axis, Y, ROTATE);
		shape->v_axis = vector_rotate(shape->v_axis, Y, ROTATE);
	}
	else if (keys->key[L])
	{
		shape->u_axis = vector_rotate(shape->u_axis, Y, (-ROTATE));
		shape->v_axis = vector_rotate(shape->v_axis, Y, (-ROTATE));
	}
	else if (keys->key[U])
	{
		shape->u_axis = vector_rotate(shape->u_axis, Z, ROTATE);
		shape->v_axis = vector_rotate(shape->v_axis, Z, ROTATE);
	}
	else if (keys->key[O])
	{
		shape->u_axis = vector_rotate(shape->u_axis, Z, (-ROTATE));
		shape->v_axis = vector_rotate(shape->v_axis, Z, (-ROTATE));
	}
}
