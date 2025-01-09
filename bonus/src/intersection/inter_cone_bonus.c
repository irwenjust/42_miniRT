#include "miniRT_bonus.h"

static bool	check_co_wall(t_cone *cone, t_hit *hit, double t)
{
	t_vector	hp;
	t_vector	vec;
	t_vector	tip_hp;
	double		offset;
	double		angle;

	if (t < 1e-8 || t > hit->distance)
		return (false);
	hp = point_on_ray(&hit->ray, t);
	vec = vector_sub(hit->ray.start, cone->tip);
	offset = vector_dot(hit->ray.normal, cone->normal) * t + vector_dot(vec, cone->normal);
	tip_hp = vector_sub(hp, cone->tip);
	angle = acos(vector_cos(cone->normal, tip_hp)) - 1e-8;
	offset -= 1e-8;
	if (offset >= 0 && offset <= cone->height && angle <= cone->angle)
	{
		hit->co_hp = vector_add(cone->tip, vector_scale(cone->normal, offset));
		// hit->offset = offset;
		hit->distance = t;
		return (true);
	}
	return (false);
}

static bool	check_co_base(t_cone *cone, t_ray *ray, t_hit *hit, t_vector base)
{
	t_plane		plane;
	t_hit		base_hit;
	t_vector	point;
	double		offset;

	plane.center = base;
	plane.normal = cone->normal;
	plane.color = cone->color;
	offset = 1e-8;
	if (inter_plane(&plane, ray, &base_hit, &offset))
	{
		if (base_hit.distance < 1e-8 || base_hit.distance > hit->distance)
			return (false);
		point = point_on_ray(&hit->ray, base_hit.distance);
		offset = vector_magnitude(vector_sub(point, base));
		if (offset >= 0 && offset <= cone->radius)
		{
			hit->co_hp = cone->normal;
			hit->distance = base_hit.distance;
			return (true);
		}
	}
	return (false);
}

static double	hit_cone(t_cone *cone, t_ray *ray, t_equation *eq, t_hit *hit)
{
	hit->distance = INFINITY;
	hit->ray = *ray;
	check_co_wall(cone, hit, eq->t1);
	check_co_wall(cone, hit, eq->t2);
	check_co_base(cone, ray, hit, cone->base);
	if (hit->distance == INFINITY)
		return (0);
	return (hit->distance);
}

static void	init_cone_equation(t_cone *cone, t_ray *ray, t_equation *eq)
{
	t_vector	vec;
	
	vec = vector_sub(ray->start, cone->tip);
	eq->a = pow(vector_dot(ray->normal, cone->normal), 2) - pow(cos(cone->angle), 2);
	eq->b = 2.0f * (vector_dot(ray->normal, cone->normal) * vector_dot(vec, cone->normal) - vector_dot(ray->normal, vec) * pow(cos(cone->angle), 2));
	eq->c = pow(vector_dot(vec, cone->normal), 2) - vector_dot(vec, vec) * pow(cos(cone->angle), 2);
	eq->t1 = -1;
	eq->t2 = -1;
}

bool	inter_cone(t_cone *cone, t_ray *ray, t_hit *hit, double *valid_t)
{
	t_equation	eq;
	double		distance;

	init_cone_equation(cone, ray, &eq);
	if (solve(&eq) != -1  && (eq.t1 > 1e-8 || eq.t2 > 1e-8))
	{
		distance = hit_cone(cone, ray, &eq, hit);
		if (distance > 0.0f)
		{
			hit->distance = distance;
			hit->color = cone->color;
			find_valid_t(&eq);
			*valid_t = eq.t1;
			return (*valid_t > 0);
		}
	}
	return (false);
}
