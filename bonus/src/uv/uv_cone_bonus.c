/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_cone_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:19:25 by likong            #+#    #+#             */
/*   Updated: 2025/02/17 15:46:42 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static void	slide_mapping(t_vector apex, t_hit *hit, double *u, double *v)
{
	t_vector	point;
	double		dist_along_axis;
	double		fraction;
	double		azimuth;

	point = vector_sub(hit->hit_point, apex);
	dist_along_axis = vector_dot(point, hit->shape->data.cone.normal);
	fraction = dist_along_axis / hit->shape->data.cone.height;
	azimuth = atan2(vector_dot(point, hit->shape->v_axis),
			vector_dot(point, hit->shape->u_axis));
	if (azimuth < 0.0)
		azimuth += 2.0 * M_PI;
	*u = azimuth / (2.0 * M_PI);
	*v = fraction;
}

static void	cap_mapping(t_vector base, t_hit *hit, double *u, double *v)
{
	t_vector	local_point;
	double		px;
	double		py;

	local_point = vector_sub(hit->hit_point, base);
	px = vector_dot(local_point, hit->shape->u_axis);
	py = vector_dot(local_point, hit->shape->v_axis);
	*u = (px / hit->shape->data.cone.radius + 1.0) * 0.5;
	*v = (py / hit->shape->data.cone.radius + 1.0) * 0.5;
}

void	cone_uv(t_hit *hit, double *u, double *v, int repeat)
{
	t_vector	apex;
	t_vector	base_center;
	double		alignment;

	apex = vector_sub(hit->shape->data.cone.center, vector_scale(
				hit->shape->data.cone.normal,
				hit->shape->data.cone.height * 0.5));
	base_center = vector_add(hit->shape->data.cone.center, vector_scale(
				hit->shape->data.cone.normal,
				hit->shape->data.cone.height * 0.5));
	alignment = fabs(vector_dot(hit->normal, hit->shape->data.cone.normal));
	if (alignment > (1.0 - 1e-6))
		cap_mapping(base_center, hit, u, v);
	else
		slide_mapping(apex, hit, u, v);
	uv_repeat_wrap(u, v, repeat);
}
