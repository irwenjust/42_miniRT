/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:50:15 by likong            #+#    #+#             */
/*   Updated: 2024/10/24 11:27:20 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	new_shpere(char **arg, t_sphere *sphere)
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
	sphere->radius = ft_atod(arg[2]) / 2.0;
	return (true);
}

bool	parse_sphere(char **arg, t_fclass *fclass)
{
	t_shape		*shape;
	t_sphere	sphere;

	if (ft_matrix_size(arg) != 4 || !check_syntax(arg, "0101"))
		return (ERROR("sphere: wrong args format"), false);
	if (ft_atod(arg[2]) / 2.0 < 1e-8)
		return (ERROR("light: wrong radius value"), false);
	if (!check_rgb(arg[3]))
		return (ERROR("light: wrong color value"), false);
	if (!new_shpere(arg, &sphere))
		return (ERROR("sphere: fail to create new shpere"), false);
	shape = new_shape(&sphere, SPHERE, fclass->size);
	push_to_fclass(fclass, shape);
	return (true);
}

/*
at^2 + bt + c = 0
a: The squared length of the ray's direction vector.
b: Twice the dot product of co and the ray's direction, 
	representing the alignment of the ray direction with 
	the sphere center.
c: The squared length of co minus the squared radius of 
	the sphere. This represents the distance from 
	the ray origin to the sphere center, adjusted by 
	the sphere's radius.
*/
bool inter_sphere(t_sphere *sphere, t_ray *ray, t_hit *inter)
{
	t_equation equation;
	t_vector vec;

	equation.root1 = -1.0f;
	vec = vector_subtract(ray->start, sphere->center);
	equation.a = vector_dot(ray->normal, ray->normal);
	equation.b = 2.0f * vector_dot(vec, ray->normal);
	equation.c = vector_dot(vec, vec) - pow(sphere->radius, 2);
	if (solve(&equation) > 0 && (equation.root1 > 1e-8 || equation.root2 > 1e-8))
	{
		if (equation.root1 > 1e-8)
			inter->distance = equation.root1;
		else
			inter->distance = equation.root2;
		inter->color = sphere->color;
		return (true);
	}
	return (false);
}

t_vector	normalize_sphere(t_hit *inter, t_ray *ray)
{
	t_vector	point;
	t_vector	normal;

	point = point_on_ray(ray, inter->distance);
	normal = vector_subtract(point, inter->shape->data.sphere.center);
	return (normal);
}
