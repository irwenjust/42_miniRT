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
 * 
 */
static bool	check_wall(t_cylinder *cy, t_hit *inter, double distance)
{
	t_vector	point;
	t_vector	co;
	t_vector	a;
	double	m;
	double	len;

	point = point_on_ray(&inter->ray, distance);
	co = vector_sub(inter->ray.start, cy->cap_u);
	m = vector_dot(inter->ray.normal, cy->normal) * distance + \
		vector_dot(co, cy->normal);
	a = vector_add(cy->cap_u, vector_multiple(cy->normal, m));
	len = vector_magnitude(vector_sub(point, a));
	m -= 1e-8;
	len -= 1e-8;
	if (m >= 0 && m <= cy->height && len <= cy->radius \
		&& distance > 1e-8 && distance < inter->distance)
	{
		inter->cy_hp = a;
		inter->distance = distance;
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
 * 
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


