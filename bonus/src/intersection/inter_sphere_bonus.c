/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_sphere_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:34:51 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:34:53 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

/**
 * @brief If the distance between center point and a point is equal to radius
 * means the point is on the sphere
 * A ray in 3d space is represented as: R(t) = O + tD
 *		O is origin of the ray, D is direction
 * 		t is a scalar parameter the determins a specific point along the ray
 * A sphere is:	(x − Cx)^2 + (y − Cy)^2 + (z − Cz)^2 = r^2
 * 		C is the center of sphere, x, y, z is a point on the sphere
 * If a ray is intersects with a sphere, substitue ray equation 
 * into the sphere equation: ((O + tD) - C)^2 = r^2
 * Simplify this equation is:
 * 		((O-C) + tD) * ((O-C) + tD) = r^2
 * 		(O−C)*(O−C) + 2t*D*(O−C) + t^2*D*D = r^2
 * 		t^2(D*D) + 2t(D*(O-C)) + ((O-C)*(O-C)-r^2) = 0
 * So at^2 + bt + c = 0
 * 		a = D*D = dot(ray.normal)
 * 		b = 2*(D*(O-C)) = 2 * ray.normal * (ray.start - sphere.center)
 * 		c = dot(ray.start - sphere.center) - radius^2
 * 			and if c < 0, the ray origin is inside the sphere
 * 				if c = 0, the ray origin in on the sphere
 * 				if c > 0, the ray origin in outside the sphere
 * @param equation equation structure
 * @param vec the vector from ray origin to sphere center point
 */
bool	inter_sphere(t_sphere *sphere, t_ray *ray, t_hit *hit)
{
	t_equation	equation;
	t_vector	vec;

	vec = vector_sub(ray->start, sphere->center);
	equation.a = vector_dot(ray->normal, ray->normal);
	equation.b = 2.0f * vector_dot(vec, ray->normal);
	equation.c = vector_dot(vec, vec) - pow(sphere->radius, 2);
	equation.t1 = -1;
	equation.t2 = -1;
	if (solve(&equation) != -1 && (equation.t1 > 1e-8 || equation.t2 > 1e-8))
	{
		if (equation.t1 > 1e-8)
			hit->distance = equation.t1;
		else
			hit->distance = equation.t2;
		hit->color = sphere->color;
		find_valid_t(&equation);
		return (equation.t1 > 1e-8);
	}
	return (false);
}
