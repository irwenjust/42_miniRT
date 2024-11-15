#include "miniRT.h"

bool	check_cap(t_cylinder *cy, t_vector cap, t_hit *inter, double t)
{
	double	len;
	t_vector	point;

	point = ray_at(&inter->ray, t);
	len = vector_len(vector_subtract(point, cap));
	len += 1e-8;
	if (len <= cy->radius && t > 1e-8 && t < inter->distance)
	{
		inter->hit_position = cap;
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

	point = ray_at(&inter->ray, distance);
	co = vector_subtract(inter->ray.start, cy->up);
	m = vector_dot(inter->ray.direct, cy->normal) * distance + \
		vector_dot(co, cy->normal);
	a = vector_add(cy->up, vector_multiple(cy->normal, m));
	len = vector_len(vector_subtract(point, a));
	m -= 1e-8;
	len -= 1e-8;
	if (m >= 0 && m <= cy->height && len <= cy->radius \
		&& distance > 1e-8 && distance < inter->distance)
	{
		inter->hit_position = a;
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
	double root3;
	double root4;

	root3 = inter_cap(cylinder, ray, cylinder->up);
	root4 = inter_cap(cylinder, ray, cylinder->down);
	inter->distance = INFINITY;
	inter->ray = *ray;
	check_wall(cylinder, inter, eq->root1);
	check_wall(cylinder, inter, eq->root2);
	check_cap(cylinder, cylinder->up, inter, root3);
	check_cap(cylinder, cylinder->down, inter, root4);
	if (inter->distance == INFINITY)
		return (0);
	return (inter->distance);
}

bool inter_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit *inter)
{
	t_equation equation;
	t_vector vec;
	double distance;

	equation.root1 = -1;
	equation.root2 = -1;
	vec = vector_subtract(ray->start, cylinder->up);
	equation.a = vector_dot(ray->direct, ray->direct) - pow(vector_dot(ray->direct, cylinder->normal), 2);
	equation.b = 2 * (vector_dot(ray->direct, vec) - (vector_dot(ray->direct, cylinder->normal) * vector_dot(vec, cylinder->normal)));
	equation.c = vector_dot(vec, vec) - pow(vector_dot(vec, cylinder->normal), 2) - pow(cylinder->radius, 2);
	solve(&equation);
	if (equation.root1 <= 0 && equation.root2 <= 0)
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