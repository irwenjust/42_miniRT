/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:37:43 by yzhan             #+#    #+#             */
/*   Updated: 2024/11/18 17:51:02 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Check wall hit validation.
 * find the hit point then map ray to cylinder axis, and calculate the offset of
 * this mapping point with cap center. This value should smaller than cylinder
 * height; Then the calculate the len between hit point and it mapping point on
 * axis, this len should be smaller than cap radius.
 * 
 * @param vec the vector from cap_u to ray origin
 * @param hit the intersect point of ray with cylinder
 * @param hit_a the vector from cap_u to the mapping hit point on axis
 * @param offset map ray to cylinder axis with t distance, and map vec to axis
 * to get the offset of hit point to cap_u
 * @param len the distance between hit and hit_a
 */
static bool	check_wall(t_cylinder *cy, t_hit *inter, double t)
{
	t_vector	vec;
	t_vector	hit;
	t_vector	hit_a;
	double	offset;
	
	double	len;

	if (t < 1e-8 || t > inter->distance)
		return (false);
	hit = point_on_ray(&inter->ray, t);
	vec = vector_sub(inter->ray.start, cy->cap_u);
	offset = vector_dot(inter->ray.normal, cy->normal) * t + vector_dot(vec, cy->normal);
	hit_a = vector_add(cy->cap_u, vector_multiple(cy->normal, offset));
	len = vector_magnitude(vector_sub(hit, hit_a));
	offset -= 1e-8;
	len -= 1e-8;
	if (offset >= 0 && offset <= cy->height && len <= cy->radius)
	{
		inter->cy_hp = hit_a;
		inter->distance = t;
		return (true);
	}
	return (false);
}

/*
static double inter_cap(t_cylinder *cylinder, t_ray *ray, t_vector cap)
{
	t_plane plane;
	t_hit inter;
	
	plane = (t_plane)
	{
		.center = cap,
		.normal = cylinder->normal,
		.color = BLACK
	};
	if (inter_plane(&plane, ray, &inter))
		return (inter.distance);
	return (-1);
}

bool	check_cap(t_cylinder *cy, t_vector cap, t_hit *inter, double t)
{
	double	len;
	t_vector	point;

	point = point_on_ray(&inter->ray, t);
	len = vector_magnitude(vector_sub(point, cap));
	len += 1e-8;
	if (len <= cy->radius && t > 1e-8 && t < inter->distance)
	{
		inter->cy_hp = cap;
		inter->distance = t;
		return (true);
	}
	return (false);
}
*/

/**
 * @brief check whether there is a intersect point of ray and plane
 * If intersect, check the position of hit point is inside the cap range or not
 */
static bool check_cap(t_cylinder *cy, t_ray *ray, t_hit *inter, t_vector cap)
{
	t_plane plane;
	t_hit cap_inter;
	t_vector point;
	double offset;

	plane.center = cap;
	plane.normal = cy->normal;
	plane.color = BLACK;
	offset = 1e-8;
	if (inter_plane(&plane, ray, &cap_inter))
	{
		point = point_on_ray(&inter->ray, cap_inter.distance);
		offset = vector_magnitude(vector_sub(point, cap));
		if (offset <= cy->radius && cap_inter.distance > 1e-8 && cap_inter.distance < inter->distance)
		{
			inter->cy_hp = cap;
			inter->distance = cap_inter.distance;
			return (true);
		}
	}
	return (false);
}

/**
 * @brief check whether there is any hit point
 * Check wall hit first, if both two t is valid, not need to calculate the cap hit
 * If wall hit less than two, calculate is there any valid cap hit.
 * Then, there should be at least one valid hit point.
 */
double check_cy_hit(t_cylinder *cy, t_ray *ray, t_equation *eq, t_hit *inter)
{
	inter->distance = INFINITY;
	inter->ray = *ray;
	if (!check_wall(cy, inter, eq->t1) || !check_wall(cy, inter, eq->t2))
	{
		check_cap(cy, ray, inter, cy->cap_u);
		check_cap(cy, ray, inter, cy->cap_b);
	}
	if (inter->distance == INFINITY)
		return (0);
	return (inter->distance);
}


