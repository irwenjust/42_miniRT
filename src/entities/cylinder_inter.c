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

bool	check_cap(t_cylinder *cy, t_vector cap, t_hit *inter, double t)
{
	double	len;
	t_vector	point;

	point = point_on_ray(&inter->ray, t);
	len = vector_len(vector_sub(point, cap));
	len += 1e-8;
	if (len <= cy->radius && t > 1e-8 && t < inter->distance)
	{
		inter->cy_hit_pos = cap;
		inter->distance = t;
		return (true);
	}
	return (false);
}

static bool	check_wall(t_cylinder *cy, t_hit *inter, double distance)
{
	t_vector	point;
	t_vector	co;
	t_vector	a;
	double	m;
	double	len;

	point = point_on_ray(&inter->ray, distance);
	co = vector_sub(inter->ray.start, cy->up);
	m = vector_dot(inter->ray.normal, cy->normal) * distance + \
		vector_dot(co, cy->normal);
	a = vector_add(cy->up, vector_multiple(cy->normal, m));
	len = vector_len(vector_sub(point, a));
	m -= 1e-8;
	len -= 1e-8;
	if (m >= 0 && m <= cy->height && len <= cy->radius \
		&& distance > 1e-8 && distance < inter->distance)
	{
		inter->cy_hit_pos = a;
		inter->distance = distance;
		return (true);
	}
	return (false);
}

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

static double valid_cylinder_hit(t_cylinder *cylinder, t_ray *ray, t_equation *eq, t_hit *inter)
{
	double t3;
	double t4;

	t3 = inter_cap(cylinder, ray, cylinder->up);
	t4 = inter_cap(cylinder, ray, cylinder->down);
	inter->distance = INFINITY;
	inter->ray = *ray;
	check_wall(cylinder, inter, eq->t1);
	check_wall(cylinder, inter, eq->t2);
	check_cap(cylinder, cylinder->up, inter, t3);
	check_cap(cylinder, cylinder->down, inter, t4);
	if (inter->distance == INFINITY)
		return (0);
	return (inter->distance);
}

bool inter_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit *inter)
{
	t_equation equation;
	t_vector vec;
	double distance;

	equation.t1 = -1;
	equation.t2 = -1;
	vec = vector_sub(ray->start, cylinder->up);
	equation.a = vector_dot(ray->normal, ray->normal) - pow(vector_dot(ray->normal, cylinder->normal), 2);
	equation.b = 2 * (vector_dot(ray->normal, vec) - (vector_dot(ray->normal, cylinder->normal) * vector_dot(vec, cylinder->normal)));
	equation.c = vector_dot(vec, vec) - pow(vector_dot(vec, cylinder->normal), 2) - pow(cylinder->radius, 2);
	solve(&equation);
	if (equation.t1 <= 0 && equation.t2 <= 0)
		return (false);
	distance = valid_cylinder_hit(cylinder, ray, &equation, inter);
	if (distance > 0.0f)
	{
		inter->distance = distance;
		inter->color = cylinder->color;
		return (true);
	}
	return (false);
}
