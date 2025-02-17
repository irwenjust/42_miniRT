/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_sphere_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:33:38 by likong            #+#    #+#             */
/*   Updated: 2025/02/17 15:33:58 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	sphere_uv(t_hit *hit, double *u, double *v, int repeat)
{
	t_vector	local_point;
	t_shape		*shape;
	double		azimuth;
	double		polar;

	shape = hit->shape;
	local_point = hit->normal;
	local_point = (t_vector){
		vector_dot(local_point, shape->u_axis),
		vector_dot(local_point, shape->data.sphere.normal),
		vector_dot(local_point, shape->v_axis)};
	local_point = vector_normalize(local_point);
	azimuth = atan2(local_point.z, local_point.x);
	polar = acos(local_point.y);
	*u = (azimuth + PI) / (2 * PI);
	*v = polar / PI;
	uv_repeat_wrap(u, v, repeat);
}
