/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:37:43 by yzhan             #+#    #+#             */
/*   Updated: 2024/12/18 14:27:51 by likong           ###   ########.fr       */
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
	if (inter_plane(&plane, ray, &cap_inter, &offset))
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
static double check_cy_hit(t_cylinder *cy, t_ray *ray, t_equation *eq, t_hit *inter)
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

static void	init_cy_equation(t_cylinder *cylinder, t_ray *ray, t_equation *equation)
{
	t_vector vec;
	double dn;
	double vn;

	vec = vector_sub(ray->start, cylinder->cap_u);
	dn = vector_dot(ray->normal, cylinder->normal);
	vn = vector_dot(vec, cylinder->normal);
	equation->a = 1 - pow(dn, 2);
	equation->b = 2 * (vector_dot(ray->normal, vec) - (dn * vn));
	equation->c = vector_dot(vec, vec) - pow(vn, 2) - pow(cylinder->radius, 2);
	equation->t1 = -1;
	equation->t2 = -1;
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
bool inter_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit *inter, double *valid_t)
{
	t_equation	equation;
	double		distance;
	
	init_cy_equation(cylinder, ray, &equation);
	if (solve(&equation) != -1 && (equation.t1 > 1e-8 || equation.t2 > 1e-8))
	{
		distance = check_cy_hit(cylinder, ray, &equation, inter);
		if (distance > 0.0f)
		{
			inter->distance = distance;
			inter->color = cylinder->color;
			find_valid_t(equation);
			*valid_t = equation.t1;
			// printf("t1: %f, t2: %f\n", equation.t1, equation.t2);
			return (*valid_t > 0);
		}
	}
	return (false);
}
