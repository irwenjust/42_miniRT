/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:29:37 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:30:00 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static bool	new_cylinder(char **arg, t_cylinder *cy)
{
	char	**tmp;

	tmp = ft_split(arg[1], ',');
	if (!tmp)
		return (ERROR("cylinder: fail to split coordinate"), false);
	cy->center = parse_vector(tmp);
	free_matrix(tmp);
	tmp = ft_split(arg[2], ',');
	if (!tmp)
		return (ERROR("cylinder: fail to split normal"), false);
	cy->normal = parse_vector(tmp);
	if (vector_magnitude(cy->normal) < 1.0 - 1e-8)
		return (ERROR("cylinder: normal vector is too small"), false);
	cy->normal = vector_normalize(cy->normal);
	free_matrix(tmp);
	cy->radius = ft_atod(arg[3]) * 0.5;
	cy->height = ft_atod(arg[4]);
	tmp = ft_split(arg[5], ',');
	if (!tmp)
		return (ERROR("cylinder: fail to split color"), false);
	cy->color = parse_color(tmp);
	free_matrix(tmp);
	return (true);
}

bool	parse_cylinder(char **arg, t_fclass *fclass)
{
	t_shape		*shape;
	t_cylinder	cy;

	if (!new_cylinder(arg, &cy))
		return (ERROR("cylinder: fail to create new cylinder"), false);
	cy.cap_s = vector_add(cy.center, vector_scale(cy.normal, -cy.height * 0.5));
	cy.cap_e = vector_add(cy.center, vector_scale(cy.normal, cy.height * 0.5));
	shape = new_shape(&cy, CYLINDER, fclass->size, s()->shape_nbr[CYLINDER]);
	if (check_texture(arg, shape) == false)
		return (ft_free((void **)&shape), false);
	shape->ks = ft_atod(arg[6]);
	shape->shininess = ft_atod(arg[7]);
	shape->refra_idx = ft_atod(arg[11]);
	shape->transparency = ft_atod(arg[12]);
	s()->shape_nbr[CYLINDER]++;
	add_uv_axis(shape, shape->data.cylinder.normal);
	push_to_fclass(fclass, shape);
	return (true);
}

void	move_cylinder(t_key *keys, t_cylinder *cy)
{
	if (keys->key[D])
		cy->center.x += 0.3;
	else if (keys->key[A])
		cy->center.x -= 0.3;
	if (keys->key[W])
		cy->center.y += 0.3;
	else if (keys->key[S])
		cy->center.y -= 0.3;
	else if (keys->key[E])
		cy->center.z += 0.3;
	else if (keys->key[Q])
		cy->center.z -= 0.3;
	cy->cap_s = vector_add(cy->center,
			vector_scale(cy->normal, -cy->height * 0.5));
	cy->cap_e = vector_add(cy->center,
			vector_scale(cy->normal, cy->height * 0.5));
}

void	rotate_cylinder(t_key *keys, t_cylinder *cy)
{
	if (keys->key[I])
		cy->normal = vector_rotate(cy->normal, X, ROTATE);
	else if (keys->key[K])
		cy->normal = vector_rotate(cy->normal, X, (-ROTATE));
	else if (keys->key[J])
		cy->normal = vector_rotate(cy->normal, Y, ROTATE);
	else if (keys->key[L])
		cy->normal = vector_rotate(cy->normal, Y, (-ROTATE));
	else if (keys->key[U])
		cy->normal = vector_rotate(cy->normal, Z, ROTATE);
	else if (keys->key[O])
		cy->normal = vector_rotate(cy->normal, Z, (-ROTATE));
	cy->cap_s = vector_add(cy->center,
			vector_scale(cy->normal, -cy->height * 0.5));
	cy->cap_e = vector_add(cy->center,
			vector_scale(cy->normal, cy->height * 0.5));
}

void	scaling_cylinder(t_key *keys, t_cylinder *cy)
{
	if (keys->cur_keycode == LEFT && cy->radius - 0.1 > 0)
		cy->radius -= 0.1;
	else if (keys->cur_keycode == RIGHT)
		cy->radius += 0.1;
	else if (keys->cur_keycode == UP)
		cy->height += 0.1;
	else if (keys->cur_keycode == DOWN && cy->height - 0.1 > 0)
		cy->height -= 0.1;
	cy->cap_s = vector_add(cy->center,
			vector_scale(cy->normal, -cy->height * 0.5));
	cy->cap_e = vector_add(cy->center,
			vector_scale(cy->normal, cy->height * 0.5));
}
