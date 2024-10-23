/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:50:15 by likong            #+#    #+#             */
/*   Updated: 2024/10/23 20:31:15 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	check_save(char **tmp, t_sphere *sphere)
{
	char	**coordinate;
	char	**rgb;

	coordinate = ft_split(tmp[1], ',');
	if (!coordinate)
		return (ERROR("error when split sphere's coodinate"), false);
	rgb = ft_split(tmp[3], ',');
	if (!rgb)
	{
		free_matrix(coordinate);
		return (ERROR("error when split sphere's color"), false);
	}
	*sphere = (t_sphere){
		.center = save_vector(coordinate),
		.radius = ft_atod(tmp[2]) / 2.0,
		.color = save_color(rgb)
	};
	free_matrix(coordinate);
	free_matrix(rgb);
	if (sphere->radius < 1e-8) // maybe need to adjust value
		return (false);
	return (true);
}

bool	save_sphere(char **tmp, t_fclass *fclass)
{
	t_shape		*shape;
	t_sphere	sphere;

	if (ft_matrix_size(tmp) != 4)
		return (ERROR("sphere needs 4 arguments"), false);
	//more check here
	if (!check_save(tmp, &sphere))
		return (ERROR("radius too small or previous error in sphere"), false);
	shape = shape_new(&sphere, SPHERE, fclass->size);
	push_to_fclass(fclass, shape);
	return (true);
}
