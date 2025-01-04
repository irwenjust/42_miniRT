

#include "miniRT_bonus.h"

static bool	new_plane(char **arg, t_plane *plane)
{
	char	**coord;
	char	**normal;
	char	**rgb;

	coord = ft_split(arg[1], ',');
	if (!coord)
		return (ERROR("plane: fail to split coordinate"), false);
	plane->center = parse_vector(coord);
	free_matrix(coord);
	normal = ft_split(arg[2], ',');
	if (!normal)
		return (ERROR("plane: fail to split normal"), false);
	plane->normal = parse_vector(normal);
	free_matrix(normal);
	if (vector_magnitude(plane->normal) < 1e-8)
		return (ERROR("plane: normal vector is too small"), false);
	plane->normal = vector_normalize(plane->normal);
	plane->normal = vector_add(plane->normal, VEC_MIN);
	rgb = ft_split(arg[3], ',');
	if (!rgb)
		return (ERROR("plane: fail to split color"), false);
	plane->color = parse_color(rgb);
	free_matrix(rgb);
	return (true);
}

bool	parse_plane(char **arg, t_fclass *fclass)
{
	t_shape	*shape;
	t_plane	plane;

	if (ft_matrix_size(arg) != 6 || !check_syntax(arg, "0111"))
		return (ERROR("plane: wrong args format"), false);
	if (!check_rgb(arg[3]))
		return (ERROR("plane: wrong color value"), false);
	if (!new_plane(arg, &plane))
		return (ERROR("plane: fail to create new plane"), false);
	shape = new_shape(&plane, PLANE, fclass->size, s()->shape_nbr[PLANE]);
	shape->ks = ft_atod(arg[4]);
	shape->shininess = ft_atod(arg[5]);
	if (shape->ks < 1e-8 || shape->ks > 1)
		return (ERROR("plane: wrong ks value"), false);
	if (shape->shininess < 1 || shape->shininess > 128)
		return (ERROR("plane: wrong shininess value"), false);
	printf("ks %f, shininess %f\n", shape->ks, shape->shininess);
	s()->shape_nbr[PLANE]++;
	push_to_fclass(fclass, shape);
	return (true);
}

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

void	move_plane(t_key *keys, t_plane *plane)
{
	if (keys->key[D])
		plane->center.x += 0.3;
	else if (keys->key[A])
		plane->center.x -= 0.3;
	else if (keys->key[W])
		plane->center.y += 0.3;
	else if (keys->key[S])
		plane->center.y -= 0.3;
	else if (keys->key[E])
		plane->center.z += 0.3;
	else if (keys->key[Q])
		plane->center.z -= 0.3;
	printf("move plane\n");
}

void	rotate_plane(t_key *keys, t_plane *plane)
{
	if (keys->key[I])
		plane->normal = vector_rotate(plane->normal, X, ROTATE);
	else if (keys->key[K])
		plane->normal = vector_rotate(plane->normal, X, (-ROTATE));
	else if (keys->key[L])
		plane->normal = vector_rotate(plane->normal, Y, ROTATE);
	else if (keys->key[J])
		plane->normal = vector_rotate(plane->normal, Y, (-ROTATE));
	else if (keys->key[O])
		plane->normal = vector_rotate(plane->normal, Z, ROTATE);
	else if (keys->key[U])
		plane->normal = vector_rotate(plane->normal, Z, (-ROTATE));
	printf("rotate plane\n");
}

// bool	inter_real_plane(t_plane *plane, t_ray *ray, double *valid_t)
// {
// 	double		numerator;
// 	double		denominator;
// 	t_vector	vec;

// 	denominator = vector_dot(ray->normal, plane->normal);
// 	if (fabs(denominator) < 1e-6)
// 		return (false);
// 	vec = vector_sub(plane->center, ray->start);
// 	numerator = vector_dot(vec, plane->normal);
// 	*valid_t = numerator / denominator;
// 	return (*valid_t > 0.0);
// }
