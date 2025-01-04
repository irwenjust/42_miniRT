

#include "miniRT_bonus.h"

static bool	new_sphere(char **arg, t_sphere *sphere)
{
	char	**coord;
	char	**rgb;

	coord = ft_split(arg[1], ',');
	if (!coord)
		return (ERROR("sphere: fail to split coordinate"), false);
	sphere->center = parse_vector(coord);
	free_matrix(coord);
	rgb = ft_split(arg[3], ',');
	if (!rgb)
		return (ERROR("sphere: fail to split color"), false);
	sphere->color = parse_color(rgb);
	free_matrix(rgb);
	sphere->radius = ft_atod(arg[2]) * 0.5;
	sphere->box = box_sphere(sphere);
	sphere->rebuildbox = box_sphere;
	return (true);
}

bool	parse_sphere(char **arg, t_fclass *fclass)
{
	t_shape		*shape;
	t_sphere	sphere;

	if (ft_matrix_size(arg) != 6 || !check_syntax(arg, "0101"))
		return (ERROR("sphere: wrong args format"), false);
	if (ft_atod(arg[2]) * 0.5 < 1e-8)
		return (ERROR("light: wrong radius value"), false);
	if (!check_rgb(arg[3]))
		return (ERROR("light: wrong color value"), false);
	if (!new_sphere(arg, &sphere))
		return (ERROR("sphere: fail to create new shpere"), false);
	shape = new_shape(&sphere, SPHERE, fclass->size, s()->shape_nbr[SPHERE]);
	s()->shape_nbr[SPHERE]++;
	push_to_fclass(fclass, shape);
	return (true);
}

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
bool	inter_sphere(t_sphere *sphere, t_ray *ray, t_hit *hit, double *valid_t)
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
		*valid_t = equation.t1;
		return (*valid_t > 1e-8);
	}
	return (false);
}

void	move_sphere(t_key *keys, t_sphere *sphere)
{
	if (keys->key[D])
		sphere->center.x += 0.3;
	else if (keys->key[A])
		sphere->center.x -= 0.3;
	else if (keys->key[W])
		sphere->center.y += 0.3;
	else if (keys->key[S])
		sphere->center.y -= 0.3;
	else if (keys->key[E])
		sphere->center.z += 0.3;
	else if (keys->key[Q])
		sphere->center.z -= 0.3;
	sphere->box = sphere->rebuildbox(sphere);
	printf("move sphere\n");
}

void	scaling_sphere(t_key *keys, t_sphere *sphere)
{
	if (keys->cur_keycode == LEFT && sphere->radius - 0.1 > 0)
		sphere->radius -= 0.1;
	else if (keys->cur_keycode == RIGHT)
		sphere->radius += 0.1;
}
