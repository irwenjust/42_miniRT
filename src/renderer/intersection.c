/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:35:32 by yzhan             #+#    #+#             */
/*   Updated: 2024/11/27 21:34:37 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Find the intersect point for each shape
 */
bool is_intersect(t_shape *shape, t_ray *ray, t_hit *inter)
{
	if (shape->type == SPHERE)
		return (inter_sphere(&shape->data.sphere, ray, inter));
	if (shape->type == PLANE)
		return (inter_plane(&shape->data.plane, ray, inter));
	if (shape->type == CYLINDER)
		return (inter_cylinder(&shape->data.cylinder, ray, inter));
	return (false);
}

/**
 * @brief get the normal vector at the intersection point of ray and shape
 * For cylinder, if the hit_point is on caps, the normaal is constant
 * 
 */
static t_vector	get_normal(t_hit *inter)
{
	t_vector	point;
	t_vector	normal;

	point = inter->hit_point;
	if (inter->shape->type == PLANE)
		normal = inter->shape->data.plane.normal;
	else if (inter->shape->type == SPHERE)
		normal = vector_sub(point, inter->shape->data.sphere.center);
	else
	{
		normal = vector_sub(point, inter->cy_hp);
		if (vector_compare(inter->cy_hp, inter->shape->data.cylinder.cap_u))
			normal = vector_multiple(inter->shape->data.cylinder.normal, -1);
		else if (vector_compare(inter->cy_hp, inter->shape->data.cylinder.cap_b))
			normal = inter->shape->data.cylinder.normal;
	}
	return (vector_normalize(normal));
}

/**
 * @brief Check whether the ray is intersecting with any shapes and
 * find the closest intersect point.
 * Main step:
 * 		1-get the closest inter point (tmp)
 * 		2-compare distance of tmp with closest(INFINITY), 
 * 			if tmp is closer update the closest point data and return, 
 * 			if not, continue to next shape.
 * 		Go through all shapes and update the closest point then return.s
 * 
 * @param shape Get current shape
 * @param tmp The tmp cloeset intersected point
 */
bool check_intersection(t_fclass *shapes, t_ray *ray, t_hit *closest)
{
	int i;
	t_shape *shape;
	t_hit	tmp;

	i = -1;
	tmp = init_hit();
	if (!shapes)
		return (false);
	// if (!check_bvh_intersection(ray, s()->bvh, &tmp))
	// 	return (false);
	while (++i < shapes->size)
	{
		shape = shapes->array[i];
		if (!is_intersect(shape, ray, &tmp))
			continue ;
		if (tmp.distance >= closest->distance)
			continue ;
		*closest = tmp;
		closest->ray = *ray;
		closest->shape = shape;
		closest->hit_point = point_on_ray(ray, closest->distance);
		closest->hit_normal = get_normal(closest);
	}
	return (closest->shape != NULL);
}

