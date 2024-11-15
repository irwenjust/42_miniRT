/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:38:02 by yzhan             #+#    #+#             */
/*   Updated: 2024/11/15 15:38:03 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool new_cylinder(char **arg, t_cylinder *cylinder)
{
	char **coord;
	char **normal;
	char **rgb;

	coord = ft_split(arg[1], ',');
	if (!coord)
		return (ERROR("cylinder: fail to split coordinate"), false);
	cylinder->center = parse_vector(coord);
	free_matrix(coord);
	normal = ft_split(arg[2], ',');
	if (!normal)
		return (ERROR("cylinder: fail to split normal"), false);
	cylinder->normal = vector_normalize(parse_vector(normal));
	free_matrix(normal);
	if (vector_len(cylinder->normal) < 1e-8)
		return (ERROR("cylinder: normal vector is too small"), false);
	cylinder->radius = ft_atod(arg[3]) / 2.0;
	cylinder->height = ft_atod(arg[4]);
	rgb = ft_split(arg[5], ',');
	if (!rgb)
		return (ERROR("cylinder: fail to split color"), false);
	cylinder->color = parse_color(rgb);
	free_matrix(rgb);
	return (true);
}

bool parse_cylinder(char **arg, t_fclass *fclass)
{
	t_shape *shape;
	t_cylinder cylinder;

	if (ft_matrix_size(arg) != 6 || !check_syntax(arg, "011001"))
		return (ERROR("cylinder: wrong args format"), false);
	if (ft_atod(arg[3]) / 2.0 < 1e-8)
		return (ERROR("cylinder: wrong radius value"), false);
	if (ft_atod(arg[4]) < 1e-8)
		return (ERROR("cylinder: wrong height value"), false);
	if (!check_rgb(arg[5]))
		return (ERROR("cylinder: wrong color value"), false);
	if (!new_cylinder(arg, &cylinder))
		return (ERROR("cylinder: fail to create new shpere"), false);
	cylinder.up = vector_add(cylinder.center, vector_multiple(cylinder.normal, -cylinder.height / 2.0));
	cylinder.down = vector_add(cylinder.center, vector_multiple(cylinder.normal, cylinder.height / 2.0));
	shape = new_shape(&cylinder, CYLINDER, fclass->size);
	push_to_fclass(fclass, shape);
	return (true);
}

t_vector	normalize_cylinder(t_hit *inter, t_ray *ray)
{
	t_vector	point;
	t_vector	normal;

	point = point_on_ray(ray, inter->distance);
	normal = vector_subtract(point, inter->cy_hit_pos);
	if (vector_compare(inter->cy_hit_pos, inter->shape->data.cylinder.up))
		normal = vector_multiple(inter->shape->data.cylinder.normal, -1);
	else if (vector_compare(inter->cy_hit_pos, inter->shape->data.cylinder.down))
		normal = inter->shape->data.cylinder.normal;
	return (normal);
}
