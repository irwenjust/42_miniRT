/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:27:00 by likong            #+#    #+#             */
/*   Updated: 2025/02/17 14:21:33 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	check_hit_normal(t_hit *hit)
{
	if (hit->shape->type == PLANE)
		hit->normal = hit->shape->data.plane.normal;
	if (vector_dot(hit->ray.normal, hit->normal) > 0)
	{
		hit->check_hit = true;
		hit->normal = vector_scale(hit->normal, -1);
	}
}

t_vector	cone_normal(t_hit *inter)
{
	t_vector	point;
	t_vector	normal;
	t_vector	tmp;
	double		len_tip;
	double		len;

	point = inter->hit_point;
	len_tip = vector_magnitude(vector_sub(point, inter->shape->data.cone.tip));
	len = len_tip / cos(inter->shape->data.cone.angle);
	tmp = vector_add(inter->shape->data.cone.tip,
			vector_scale(inter->shape->data.cone.normal, len));
	normal = vector_sub(point, tmp);
	if (vector_compare(inter->co_hp, inter->shape->data.cone.normal))
		normal = inter->shape->data.cone.normal;
	else if (vector_compare(point, inter->shape->data.cone.tip))
		normal = vector_scale(inter->shape->data.cone.normal, -1);
	return (normal);
}

t_vector	cylinder_normal(t_hit *inter)
{
	t_vector	point;
	t_vector	normal;

	point = inter->hit_point;
	normal = vector_sub(point, inter->cy_hp);
	if (vector_compare(inter->cy_hp, inter->shape->data.cylinder.cap_s))
		normal = vector_scale(inter->shape->data.cylinder.normal, -1);
	else if (vector_compare(inter->cy_hp,
			inter->shape->data.cylinder.cap_e))
		normal = inter->shape->data.cylinder.normal;
	return (normal);
}

t_vector	sphere_normal(t_hit *inter)
{
	t_vector	point;
	t_vector	normal;
	t_vector	center;
	t_vector	ray_to_center;
	double		dot;

	point = inter->hit_point;
	center = inter->shape->data.sphere.center;
	normal = vector_sub(point, center);
	ray_to_center = vector_sub(center, inter->ray.start);
	dot = vector_dot(inter->ray.normal, ray_to_center);
	if (dot > 0)
		normal = vector_scale(normal, -1.0);
	return (normal);
}
