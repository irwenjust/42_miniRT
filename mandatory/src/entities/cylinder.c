/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:38:02 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/17 11:43:41 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	new_cylinder(char **arg, t_cylinder *cy)
{
	char	**tmp;

	tmp = ft_split(arg[1], ',');
	if (!tmp)
		return (error("cylinder: fail to split coordinate"), false);
	cy->center = parse_vector(tmp);
	free_matrix(tmp);
	tmp = ft_split(arg[2], ',');
	if (!tmp)
		return (error("cylinder: fail to split normal"), false);
	cy->normal = parse_vector(tmp);
	if (vector_magnitude(cy->normal) < 1.0 - 1e-8)
		return (error("cylinder: normal vector is too small"), false);
	cy->normal = vector_normalize(cy->normal);
	free_matrix(tmp);
	cy->radius = ft_atod(arg[3]) * 0.5;
	cy->height = ft_atod(arg[4]);
	if (cy->radius < 1e-8 || cy->height < 1e-8)
		return (error("cylinder: wrong diameter or height value"), false);
	tmp = ft_split(arg[5], ',');
	if (!tmp)
		return (error("cylinder: fail to split color"), false);
	cy->color = parse_color(tmp);
	free_matrix(tmp);
	return (true);
}

bool	parse_cylinder(char **arg, t_fclass *fclass)
{
	t_shape		*shape;
	t_cylinder	cy;

	if (ft_matrix_size(arg) != 6 || !check_arg_format(arg, "211001"))
		return (error("cylinder: wrong args format"), false);
	if (!check_rgb(arg[5]))
		return (error("cylinder: wrong color value"), false);
	if (!new_cylinder(arg, &cy))
		return (error("cylinder: fail to create new cylinder"), false);
	cy.cap_s = vector_add(cy.center,
			vector_scale(cy.normal, -cy.height * 0.5));
	cy.cap_e = vector_add(cy.center,
			vector_scale(cy.normal, cy.height * 0.5));
	shape = new_shape(&cy, CYLINDER, fclass->size, s()->shape_nbr[CYLINDER]);
	s()->shape_nbr[CYLINDER]++;
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
