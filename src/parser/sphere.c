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

static bool	check_save(char **arg, t_sphere *sphere)
{
	char	**coordinate;
	char	**rgb;

	coordinate = ft_split(arg[1], ',');
	if (!coordinate)
		return (ERROR("sphere: error when split coodinate"), false);
	rgb = ft_split(arg[3], ',');
	if (!rgb)
	{
		free_matrix(coordinate);
		return (ERROR("sphere: error when split color"), false);
	}
	*sphere = (t_sphere)
	{
		.center = parse_vector(coordinate),
		.radius = ft_atod(arg[2]) / 2.0,
		.color = parse_color(rgb)
	};
	free_matrix(coordinate);
	free_matrix(rgb);
	if (sphere->radius < 1e-8) // maybe need to adjust value
		return (false);
	return (true);
}

bool	parse_sphere(char **arg, t_fclass *fclass)
{
	t_shape		*shape;
	t_sphere	sphere;

	if (ft_matrix_size(arg) != 4)
		return (ERROR("sphere: needs 4 arguments"), false);
	//if (!check_syntax(arg, "0101"))
	//	return (ERROR("sphere: Misconfiguration in commas/numbers"), false);
	if (!check_save(arg, &sphere))
		return (ERROR("sphere: radius too small or previous error"), false);
	shape = shape_new(&sphere, SPHERE, fclass->size);
	push_to_fclass(fclass, shape);
	return (true);
}
