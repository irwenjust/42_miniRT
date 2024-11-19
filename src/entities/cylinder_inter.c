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
	co = vector_sub(inter->ray.start, cy->cap_u);
	m = vector_dot(inter->ray.normal, cy->normal) * distance + \
		vector_dot(co, cy->normal);
	a = vector_add(cy->cap_u, vector_multiple(cy->normal, m));
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

	t3 = inter_cap(cylinder, ray, cylinder->cap_u);
	t4 = inter_cap(cylinder, ray, cylinder->cap_b);
	inter->distance = INFINITY;
	inter->ray = *ray;
	check_wall(cylinder, inter, eq->t1);
	check_wall(cylinder, inter, eq->t2);
	check_cap(cylinder, cylinder->cap_u, inter, t3);
	check_cap(cylinder, cylinder->cap_b, inter, t4);
	if (inter->distance == INFINITY)
		return (0);
	return (inter->distance);
}

/**
 * @brief
 * cylinder equation is |(P-C) - [(P-C)*N]*N|^2 = r^2
 * 		P is a point on the cylinder surface
 * 		C is a point on the cylinder axis(cap)
 * 		N is cylinder direction
 * P is the R(t) = O + tD
 * The eqaution is: |(O + tD - C) - [(O + tD - C)*N]*N|^2 = r^2
 * set V = O-C
 * 		|V + tD - (V*N + tD*N)*N|^2 - r^2 = 0
 * 		|t[D - (D*N)N] + [V-(V*N)N]|^2 - r^2 = 0
 * 		t^2*[D-(D*N)N]^2 + 2t*[D-(D*N)N]*[V-(V*N)N] + [V-(V*N)N]^2 -r^2 = 0
 * So at^2 + bt + c = 0:
 * 		a = [D-(D*N)N]^2 = D*D -2(D*N)^2 + (D*N)^2*N^2
 * 		b = 2*[D-(D*N)N]*[V-(V*N)N] = 2*(D*V - D(V*N)N -V(D*N)N + (D*N)(V*N)*N^2
 * 		c = [V-(V*N)N]^2 -r^2 = V^2 - 2(V*N)^2 + (V*N)^2*N^2 - r^2
 * as normal * normal = 1, so D*D = N*N = 1
 * 		a = 1 - (D*N)^2
 * 		b = 2 * [D*V - (D*N)(V*N)]
 * 		c = V^2 - (V*N)^2 - r^2
 * 
 * @param vec vector from ray origin to cylinder cap center
 * @param dn dot_product(D, N), D is ray normal, N is cylinder norml
 * @param vn dot_product(vec, N) 
 */
bool inter_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit *inter)
{
	t_equation equation;
	t_vector vec;
	double dn;
	double vn;
	double distance;

	vec = vector_sub(ray->start, cylinder->cap_u);
	dn = vector_dot(ray->normal, cylinder->normal);
	vn = vector_dot(vec, cylinder->normal);
	equation.a = 1 - pow(dn, 2);
	equation.b = 2 * (vector_dot(ray->normal, vec) - (dn * vn));
	equation.c = vector_dot(vec, vec) - pow(vn, 2) - pow(cylinder->radius, 2);
	equation.t1 = -1;
	equation.t2 = -1;
	if (solve(&equation) && (equation.t1 > 1e-8 || equation.t2 > 1e-8))
	{
		distance = valid_cylinder_hit(cylinder, ray, &equation, inter);
		if (distance > 0.0f)
		{
			inter->distance = distance;
			inter->color = cylinder->color;
			return (true);
		}
	}
	return (false);
}
