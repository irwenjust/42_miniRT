/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:35:32 by yzhan             #+#    #+#             */
/*   Updated: 2025/01/16 19:22:59 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
bool	is_intersect(t_shape *shape, t_ray *ray, t_hit *inter, double *valid_t)
{
	bool	checker;

	checker = false;
	*valid_t = 0;
	if (shape->type == SPHERE)
		checker = inter_sphere(&shape->data.sphere, ray, inter, valid_t);
	if (shape->type == PLANE)
		checker = inter_plane(&shape->data.plane, ray, inter, valid_t);
	if (shape->type == CYLINDER)
		checker = inter_cylinder(&shape->data.cylinder, ray, inter, valid_t);
	if (*valid_t < 0)
		return (false);
	return (checker && *valid_t > 0);
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
		if (vector_compare(inter->cy_hp, inter->shape->data.cylinder.cap_s))
			normal = vector_scale(inter->shape->data.cylinder.normal, -1);
		else if (vector_compare(inter->cy_hp,
				inter->shape->data.cylinder.cap_e))
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
bool	check_intersection(t_fclass *shapes, t_ray *ray, t_hit *closest)
{
	int		i;
	t_shape	*shape;
	t_hit	tmp;
	double	checker;

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
		if (!is_intersect(shape, ray, &tmp, &checker))
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
