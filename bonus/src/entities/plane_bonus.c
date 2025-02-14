/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:29:09 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:29:14 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static bool	new_plane(char **arg, t_plane *plane)
{
	char	**tmp;

	tmp = ft_split(arg[1], ',');
	if (!tmp)
		return (ERROR("plane: fail to split coordinate"), false);
	plane->center = parse_vector(tmp);
	free_matrix(tmp);
	tmp = ft_split(arg[2], ',');
	if (!tmp)
		return (ERROR("plane: fail to split normal"), false);
	plane->normal = parse_vector(tmp);
	if (vector_magnitude(plane->normal) < 1.0 - 1e-8)
		return (ERROR("plane: normal vector is too small"), false);
	plane->normal = vector_add(plane->normal, VEC_MIN);
	plane->normal = vector_normalize(plane->normal);
	free_matrix(tmp);
	tmp = ft_split(arg[3], ',');
	if (!tmp)
		return (ERROR("plane: fail to split color"), false);
	plane->color = parse_color(tmp);
	free_matrix(tmp);
	return (true);
}

bool	parse_plane(char **arg, t_fclass *fclass)
{
	t_shape	*shape;
	t_plane	plane;

	if (!new_plane(arg, &plane))
		return (ERROR("plane: fail to create new plane"), false);
	shape = new_shape(&plane, PLANE, fclass->size, s()->shape_nbr[PLANE]);
	if (check_texture(arg, shape) == false)
		return (ft_free((void **)&shape), false);
	shape->ks = ft_atod(arg[4]);
	shape->shininess = ft_atod(arg[5]);
	shape->refra_idx = ft_atod(arg[9]);
	shape->transparency = ft_atod(arg[10]);
	s()->shape_nbr[PLANE]++;
	add_uv_axis(shape, shape->data.plane.normal);
	push_to_fclass(fclass, shape);
	return (true);
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
	else if (keys->key[J])
		plane->normal = vector_rotate(plane->normal, Y, ROTATE);
	else if (keys->key[L])
		plane->normal = vector_rotate(plane->normal, Y, (-ROTATE));
	else if (keys->key[U])
		plane->normal = vector_rotate(plane->normal, Z, ROTATE);
	else if (keys->key[O])
		plane->normal = vector_rotate(plane->normal, Z, (-ROTATE));
	printf("rotate plane\n");
}
