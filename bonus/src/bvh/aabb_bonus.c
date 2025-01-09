
#include "miniRT_bonus.h"

t_aabb	box_sphere(t_sphere *sphere)
{
	t_vector	radius_vec;
	t_aabb		sphere_box;

	radius_vec = (t_vector){sphere->radius, sphere->radius, sphere->radius};
	sphere_box.min = vector_sub(sphere->center, radius_vec);
	sphere_box.max = vector_add(sphere->center, radius_vec);
	return (sphere_box);
}

t_aabb	box_cylinder(t_cylinder *cy)
{
	t_vector	radius_vec;
	t_vector	start;
	t_vector	end;
	t_aabb		cylinder_box;

	start = vector_sub(cy->center, vector_scale(cy->normal, cy->height * 0.5));
	end = vector_add(cy->center, vector_scale(cy->normal, cy->height * 0.5));
	radius_vec = (t_vector){cy->radius, cy->radius, cy->radius};
	cylinder_box.min = vector_sub(vector_min(start, end), radius_vec);
	cylinder_box.max = vector_add(vector_max(start, end), radius_vec);
	return (cylinder_box);
}

t_aabb	box_cone(t_cone *cone)
{
	t_vector	radius_vec;
	t_vector	base_min;
	t_vector	base_max;
	t_aabb	cone_box;

	radius_vec = (t_vector){cone->radius, cone->radius, cone->radius};
	base_min = vector_sub(cone->base, radius_vec);
	base_max = vector_add(cone->base, radius_vec);
	cone_box.min = vector_min(base_min, cone->tip);
	cone_box.max = vector_max(base_max, cone->tip);
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
	{
		box = box_cone(&(shape->data.cone));
		print_box(shape->box);
	}
	return (box);
}
