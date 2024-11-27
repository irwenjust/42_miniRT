/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:08:25 by likong            #+#    #+#             */
/*   Updated: 2024/11/27 21:30:49 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_aabb	box_sphere(t_sphere *sphere)
{
	t_vector	radius_vec;
	t_aabb		sphere_box;

	radius_vec = (t_vector){sphere->radius, sphere->radius, sphere->radius};
	sphere_box.min = vector_sub(sphere->center, radius_vec);
	sphere_box.max = vector_add(sphere->center, radius_vec);
	return (sphere_box);
}

t_aabb	box_cylinder(t_cylinder *cyl)
{
	t_vector	radius_vec;
	t_vector	start;
	t_vector	end;
	t_aabb		cylinder_box;

	start = vector_sub(
			cyl->center,
			vector_scale(cyl->normal, cyl->height * 0.5));
	end = vector_add(cyl->center, vector_scale(cyl->normal, cyl->height * 0.5));
	radius_vec = (t_vector){cyl->radius, cyl->radius, cyl->radius};
	cylinder_box.min = vector_sub(vector_min(start, end), radius_vec);
	cylinder_box.max = vector_add(vector_max(start, end), radius_vec);
	// printf("AABB min: (%f, %f, %f), max: (%f, %f, %f)\n",
    //        cylinder_box.min.x, cylinder_box.min.y, cylinder_box.min.z,
    //        cylinder_box.max.x, cylinder_box.max.y, cylinder_box.max.z);
	return (cylinder_box);
}
