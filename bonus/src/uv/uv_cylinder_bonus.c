/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_cylinder_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:32:47 by likong            #+#    #+#             */
/*   Updated: 2025/02/17 15:33:06 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	cylinder_uv(t_hit *hit, double *u, double *v, int repeat)
{
	t_vector	point;
	t_vector	ua;
	t_vector	va;
	double		azimuth;
	double		height;

	ua = hit->shape->u_axis;
	va = hit->shape->v_axis;
	point = vector_sub(hit->hit_point, hit->shape->data.cylinder.center);
	height = vector_dot(point, hit->shape->data.cylinder.normal);
	height = hit->shape->data.cylinder.height / 2 + height;
	if (fabs(vector_dot(hit->normal, hit->shape->data.cylinder.normal))
		> 1 - 1e-6)
	{
		*u = (vector_dot(point, ua) / hit->shape->data.cylinder.radius + 1) / 2;
		*v = (vector_dot(point, va) / hit->shape->data.cylinder.radius + 1) / 2;
	}
	else
	{
		azimuth = atan2(vector_dot(point, va), vector_dot(point, ua));
		*u = (azimuth + PI) / (2 * PI);
		*v = height / hit->shape->data.cylinder.height;
	}
	uv_repeat_wrap(u, v, repeat);
}
