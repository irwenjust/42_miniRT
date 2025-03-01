/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:39:03 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/18 10:18:24 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	new_plane(char **arg, t_plane *plane)
{
	char	**tmp;

	tmp = ft_split(arg[1], ',');
	if (!tmp)
		return (error("plane: fail to split coordinate"), false);
	plane->center = parse_vector(tmp);
	free_matrix(tmp);
	tmp = ft_split(arg[2], ',');
	if (!tmp)
		return (error("plane: fail to split normal"), false);
	plane->normal = parse_vector(tmp);
	free_matrix(tmp);
	if (vector_magnitude(plane->normal) < 1.0 - 1e-8)
		return (error("plane: normal vector is too small"), false);
	plane->normal = vector_add(plane->normal, s()->vec_min);
	plane->normal = vector_normalize(plane->normal);
	tmp = ft_split(arg[3], ',');
	if (!tmp)
		return (error("plane: fail to split color"), false);
	plane->color = parse_color(tmp);
	free_matrix(tmp);
	return (true);
}

bool	parse_plane(char **arg, t_fclass *fclass)
{
	t_shape	*shape;
	t_plane	plane;

	if (ft_matrix_size(arg) != 4 || !check_arg_format(arg, "2111"))
		return (error("plane: wrong args format"), false);
	if (!check_rgb(arg[3]))
		return (error("plane: wrong color value"), false);
	if (!new_plane(arg, &plane))
		return (error("plane: fail to create new plane"), false);
	shape = new_shape(&plane, PLANE, fclass->size, s()->shape_nbr[PLANE]);
	if (!shape)
		return (error("plane: fail to create new shape"), false);
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
bool	inter_plane(t_plane *plane, t_ray *ray, t_hit *inter)
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
			return (equation.t1 > 1e-8);
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
}

void	rotate_plane(t_key *keys, t_plane *plane)
{
	if (keys->key[I])
		plane->normal = vector_rotate(plane->normal, X, ROTATE);
	else if (keys->key[K])
		plane->normal = vector_rotate(plane->normal, X, (-ROTATE));
	else if (keys->key[J])
		plane->normal = vector_rotate(plane->normal, Y, ROTATE);
	else if (keys->key[L])
		plane->normal = vector_rotate(plane->normal, Y, (-ROTATE));
	else if (keys->key[U])
		plane->normal = vector_rotate(plane->normal, Z, ROTATE);
	else if (keys->key[O])
		plane->normal = vector_rotate(plane->normal, Z, (-ROTATE));
}
