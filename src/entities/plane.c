/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:39:03 by yzhan             #+#    #+#             */
/*   Updated: 2024/11/18 14:34:27 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool new_plane(char **arg, t_plane *plane)
{
	char **coord;
	char **normal;
	char **rgb;

	coord = ft_split(arg[1], ',');
	if (!coord)
		return (ERROR("plane: fail to split coordinate"), false);
	plane->center = parse_vector(coord);
	free_matrix(coord);
	normal = ft_split(arg[2], ',');
	if (!normal)
		return (ERROR("plane: fail to split normal"), false);
	plane->normal = vector_normalize(parse_vector(normal));
	free_matrix(normal);
	if (vector_len(plane->normal) < 1e-8)
		return (ERROR("plane: normal vector is too small"), false);
	rgb = ft_split(arg[3], ',');
	if (!rgb)
		return (ERROR("sphere: fail to split color"), false);
	plane->color = parse_color(rgb);
	free_matrix(rgb);
	return (true);
}

bool parse_plane(char **arg, t_fclass *fclass)
{
	t_shape *shape;
	t_plane plane;
	
	if (ft_matrix_size(arg) != 4 || !check_syntax(arg, "0111"))
		return (ERROR("plane: wrong args format"), false);
	if (!check_rgb(arg[3]))
		return (ERROR("plane: wrong color value"), false);
	if (!new_plane(arg, &plane))
		return (ERROR("plane: fail to create new plane"), false);
	shape = new_shape(&plane, PLANE, fclass->size);
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
bool inter_plane(t_plane *plane, t_ray *ray, t_hit *inter)
{
	t_equation equation;
	t_vector vec;

	if (vector_dot(ray->normal, plane->normal) != 0.0)
	{
		vec = vector_sub(ray->start, plane->center);
		equation.a = 0;
		equation.b = vector_dot(ray->normal, plane->normal);
		equation.c = vector_dot(vec, plane->normal);
		equation.t1 = -1;
		equation.t2 = -1;
		//solve(&equation);
		if (solve(&equation) && equation.t1 > 1e-8)
		{
			inter->distance = equation.t1;
			inter->color = plane->color;
			return (true);
		}
	}
	return (false);
}
