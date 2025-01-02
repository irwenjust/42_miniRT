

#include "miniRT_bonus.h"

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
	double		offset;
	double		len;

	if (t < 1e-8 || t > inter->distance)
		return (false);
	hit = point_on_ray(&inter->ray, t);
	vec = vector_sub(inter->ray.start, cy->cap_u);
	offset = vector_dot(inter->ray.normal, cy->normal) * t
		+ vector_dot(vec, cy->normal);
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

/**
 * @brief check whether there is a intersect point of ray and plane
 * If intersect, check the position of hit point is inside the cap range or not
 */
static bool	check_cap(t_cylinder *cy, t_ray *ray, t_hit *inter, t_vector cap)
{
	t_plane		plane;
	t_hit		cap_inter;
	t_vector	point;
	double		offset;

	plane.center = cap;
	plane.normal = cy->normal;
	plane.color = BLACK;
	offset = 1e-8;
	if (inter_plane(&plane, ray, &cap_inter, &offset))
	{
		point = point_on_ray(&inter->ray, cap_inter.distance);
		offset = vector_magnitude(vector_sub(point, cap));
		if (offset <= cy->radius && cap_inter.distance > 1e-8
			&& cap_inter.distance < inter->distance)
		{
			inter->cy_hp = cap;
			inter->distance = cap_inter.distance;
			return (true);
		}
	}
	return (false);
}

static void	init_cy_equation(t_cylinder *cylinder, t_ray *ray, t_equation *eq)
{
	t_vector	vec;
	double		dn;
	double		vn;

	vec = vector_sub(ray->start, cylinder->cap_u);
	dn = vector_dot(ray->normal, cylinder->normal);
	vn = vector_dot(vec, cylinder->normal);
	eq->a = 1 - pow(dn, 2);
	eq->b = 2 * (vector_dot(ray->normal, vec) - (dn * vn));
	eq->c = vector_dot(vec, vec) - pow(vn, 2) - pow(cylinder->radius, 2);
	eq->t1 = -1;
	eq->t2 = -1;
}

/**
 * @brief check whether there is any hit point
 * Check wall hit first, if both two t is valid, not need to calculate cap hit
 * If wall hit less than two, calculate is there any valid cap hit.
 * Then, there should be at least one valid hit point.
 */
static double	hit_cy(t_cylinder *cy, t_ray *ray, t_equation *eq, t_hit *hit)
{
	hit->distance = INFINITY;
	hit->ray = *ray;
	if (!check_wall(cy, hit, eq->t1) || !check_wall(cy, hit, eq->t2))
	{
		check_cap(cy, ray, hit, cy->cap_u);
		check_cap(cy, ray, hit, cy->cap_b);
	}
	if (hit->distance == INFINITY)
		return (0);
	return (hit->distance);
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
bool	inter_cylinder(t_cylinder *cy, t_ray *ray, t_hit *hit, double *valid_t)
{
	t_equation	equation;
	double		distance;

	init_cy_equation(cy, ray, &equation);
	if (solve(&equation) != -1 && (equation.t1 > 1e-8 || equation.t2 > 1e-8))
	{
		distance = hit_cy(cy, ray, &equation, hit);
		if (distance > 0.0f)
		{
			hit->distance = distance;
			hit->color = cy->color;
			find_valid_t(&equation);
			*valid_t = equation.t1;
			return (*valid_t > 0);
		}
	}
	return (false);
}
