
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
	t_vector	abs_normal;
	t_vector	extent_vec;
	t_aabb		cylinder_box;
	
	// radius_vec = (t_vector){cy->radius, cy->radius, cy->radius};
	abs_normal = vector_abs(cy->normal);
	extent_vec = vector_sub((t_vector){1.0, 1.0, 1.0}, abs_normal);
	radius_vec = vector_scale(extent_vec, cy->radius);
	cylinder_box.min = vector_sub(vector_min(cy->cap_s, cy->cap_e), radius_vec);
	cylinder_box.max = vector_add(vector_max(cy->cap_s, cy->cap_e), radius_vec);
	return (cylinder_box);
}

static t_aabb	box_cone(t_cone *cone)
{
	t_vector	radius_vec;
	t_vector	abs_normal;
	t_vector	extent_vec;
	t_aabb	cone_box;

	abs_normal = vector_abs(cone->normal);
	extent_vec = vector_sub((t_vector){1.0, 1.0, 1.0}, abs_normal);
	radius_vec = vector_scale(extent_vec, cone->radius);
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
