/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_plane_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:34:29 by likong            #+#    #+#             */
/*   Updated: 2025/02/17 15:34:45 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	plane_uv(t_hit *hit, double *u, double *v, int repeat)
{
	t_vector	u_axis;
	t_vector	v_axis;
	t_vector	local_point;

	local_point = vector_sub(hit->hit_point, hit->shape->data.plane.center);
	u_axis = hit->shape->u_axis;
	v_axis = hit->shape->v_axis;
	*u = vector_dot(u_axis, local_point) * 0.01;
	*v = vector_dot(v_axis, local_point) * 0.01;
	uv_repeat_wrap(u, v, repeat);
}
