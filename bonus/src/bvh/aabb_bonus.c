/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:07:14 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:07:18 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static t_aabb	box_sphere(t_sphere *sphere)
{
	t_vector	radius_vec;
	t_aabb		sphere_box;

	radius_vec = (t_vector){sphere->radius, sphere->radius, sphere->radius};
	sphere_box.min = vector_sub(sphere->center, radius_vec);
	sphere_box.max = vector_add(sphere->center, radius_vec);
	return (sphere_box);
}

static t_aabb	box_cylinder(t_cylinder *cy)
{
	t_vector	radius_vec;
	t_aabb		cylinder_box;

	radius_vec = (t_vector){cy->radius, cy->radius, cy->radius};
	cylinder_box.min = vector_sub(vector_min(cy->cap_s, cy->cap_e), radius_vec);
	cylinder_box.max = vector_add(vector_max(cy->cap_s, cy->cap_e), radius_vec);
	return (cylinder_box);
}

static t_aabb	box_cone(t_cone *cone)
{
	t_vector	radius_vec;
	t_aabb		cone_box;

	radius_vec = (t_vector){cone->radius, cone->radius, cone->radius};
	cone_box.min = vector_sub(vector_min(cone->tip, cone->base), radius_vec);
	cone_box.max = vector_add(vector_max(cone->tip, cone->base), radius_vec);
	return (cone_box);
}

t_aabb	shape_box(t_shape *shape)
{
	t_aabb	box;

	ft_bzero(&box, sizeof(t_aabb));
	if (shape->type == SPHERE)
		box = box_sphere(&(shape->data.sphere));
	else if (shape->type == CYLINDER)
		box = box_cylinder(&(shape->data.cylinder));
	else if (shape->type == CONE)
		box = box_cone(&(shape->data.cone));
	return (box);
}
