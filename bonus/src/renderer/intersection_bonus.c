/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:47:45 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/17 14:22:00 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	find_valid_t(t_equation *equation)
{
	if (equation->t1 < 0)
		equation->t1 = INFINITY;
	if (equation->t2 < 0)
		equation->t2 = INFINITY;
	if (equation->t1 > equation->t2)
		ft_swap_d(&equation->t1, &equation->t2);
}

/**
 * @brief Find the intersect point for each shape
 */
bool	is_intersect(t_shape *shape, t_ray *ray, t_hit *inter)
{
	bool	checker;

	checker = false;
	if (shape->type == SPHERE)
		checker = inter_sphere(&shape->data.sphere, ray, inter);
	else if (shape->type == PLANE)
		checker = inter_plane(&shape->data.plane, ray, inter);
	else if (shape->type == CYLINDER)
		checker = inter_cylinder(&shape->data.cylinder, ray, inter);
	else if (shape->type == CONE)
		checker = inter_cone(&shape->data.cone, ray, inter);
	return (checker);
}

/**
 * @brief get the normal vector at the intersection point of ray and shape
 * For cylinder, if the hit_point is on caps, the normaal is constant
 * 
 */
static t_vector	get_normal(t_hit *inter)
{
	t_vector	normal;

	normal = (t_vector){0, 0, 0};
	if (inter->shape->type == PLANE)
		normal = inter->shape->data.plane.normal;
	else if (inter->shape->type == SPHERE)
		normal = sphere_normal(inter);
	else if (inter->shape->type == CYLINDER)
		normal = cylinder_normal(inter);
	else if (inter->shape->type == CONE)
		normal = cone_normal(inter);
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
bool	check_intersection(t_fclass *shapes, t_ray *ray, t_hit *closest)
{
	int		i;
	t_shape	*shape;
	t_hit	tmp;

	i = -1;
	if (!shapes)
		return (false);
	tmp = init_hit();
	if (s()->bvh)
		tmp.check_hit |= check_bvh_intersection(ray, s()->bvh, &tmp);
	if (!tmp.check_hit && s()->shape_nbr[PLANE] == 0)
		return (false);
	while (++i < shapes->size)
	{
		shape = shapes->array[i];
		if (!is_intersect(shape, ray, &tmp)
			|| tmp.distance >= closest->distance)
			continue ;
		*closest = tmp;
		closest->ray = *ray;
		closest->shape = shape;
		closest->hit_point = point_on_ray(ray, closest->distance);
		closest->normal = get_normal(closest);
	}
	return (closest->shape != NULL);
}
