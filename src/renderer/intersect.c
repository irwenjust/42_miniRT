/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:35:32 by yzhan             #+#    #+#             */
/*   Updated: 2024/11/18 15:11:06 by likong           ###   ########.fr       */
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
bool check_intersect(t_fclass *shapes, t_ray *ray, t_hit *closest)
{
	int i;
	t_shape *shape;
	t_hit	tmp;

	i = -1;
	tmp.distance = INFINITY;
	tmp.shape = NULL;
	if (!shapes)
		return (false);
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
		closest->hit_normal = vector_normalize(normalize_shape(closest, ray));
	}
	return (closest->shape != NULL);
}

