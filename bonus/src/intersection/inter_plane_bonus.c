#include "miniRT_bonus.h"

/**
 * @brief Check if the ray is intersect with the plane.
 * if the dot(ray->normal, plane->normal) == 0
 * plane equation is: (P-C)*N = 0
 * 		P any point on the plane
 * 		C the center point of the plane
 * 		N the plane normal vector
 * ray equation is: R(t) = O + tD
 * So the equation is: ((O + tD) - C) * N = 0
 * expand: (O-C+tD)*N = 0
 * 			(D*N)*t + (O-C)*N = 0
 * =>at^2 + bt + c = 0
 * 		a = 0,
 * 		b = D * N
 * 		c = (O-C)*N
 * 
 * @param vec ray origin to plane center (O-C)
 */
bool	inter_plane(t_plane *plane, t_ray *ray, t_hit *inter, double *valid_t)
{
	t_equation	equation;
	t_vector	vec;

	if (vector_dot(ray->normal, plane->normal) != 0.0)
	{
		vec = vector_sub(ray->start, plane->center);
		equation.a = 0;
		equation.b = vector_dot(ray->normal, plane->normal);
		equation.c = vector_dot(vec, plane->normal);
		equation.t1 = -1;
		equation.t2 = -1;
		if (solve(&equation) != -1 && equation.t1 > 1e-8)
		{
			inter->distance = equation.t1;
			inter->color = plane->color;
			find_valid_t(&equation);
			*valid_t = equation.t1;
			return (true);
		}
	}
	return (false);
}