
#include "miniRT_bonus.h"

void	find_valid_t(t_equation *equation)
{
	if (equation->t1 < 0)
		equation->t1 = INFINITY;
	if (equation->t2 < 0)
		equation->t2 = INFINITY;
	if (equation->t1 > equation->t2)
		ft_swap_d(&equation->t1, &equation->t2);
}

/**
 * @brief Find the intersect point for each shape
 */
bool	is_intersect(t_shape *shape, t_ray *ray, t_hit *inter, double *valid_t)
{
	bool	checker;

	checker = false;
	*valid_t = 0;
	if (shape->type == SPHERE)
		checker = inter_sphere(&shape->data.sphere, ray, inter, valid_t);
	else if (shape->type == PLANE)
		checker = inter_plane(&shape->data.plane, ray, inter, valid_t);
	else if (shape->type == CYLINDER)
		checker = inter_cylinder(&shape->data.cylinder, ray, inter, valid_t);
	else if (shape->type == CONE)
		checker = inter_cone(&shape->data.cone, ray, inter, valid_t);
	if (*valid_t < 0)
		return (false);
	return (checker && *valid_t > 0);
}

t_vector	cone_normal(t_hit *inter)
{
	t_vector	point;
	t_vector	normal;
	t_vector	tmp;
	double		len_tip;
	double		len;

	point = inter->hit_point;
	len_tip = vector_magnitude(vector_sub(point, inter->shape->data.cone.tip));
	len = len_tip / cos(inter->shape->data.cone.angle);
	tmp = vector_add(inter->shape->data.cone.tip, vector_scale(inter->shape->data.cone.normal, len));
	normal = vector_sub(point, tmp);
	if (vector_compare(inter->co_hp, inter->shape->data.cone.normal))
		normal = inter->shape->data.cone.normal;
	else if (vector_compare(point, inter->shape->data.cone.tip))
		normal = vector_scale(inter->shape->data.cone.normal, -1);
	return (normal);
}

/**
 * @brief get the normal vector at the intersection point of ray and shape
 * For cylinder, if the hit_point is on caps, the normaal is constant
 * 
 */
static t_vector	get_normal(t_hit *inter)
{
	t_vector	point;
	t_vector	normal;

	point = inter->hit_point;
	normal = (t_vector){0, 0, 0};
	if (inter->shape->type == PLANE)
		normal = inter->shape->data.plane.normal;
	else if (inter->shape->type == SPHERE)
		normal = vector_sub(point, inter->shape->data.sphere.center);
	else if (inter->shape->type == CYLINDER)
	{
		normal = vector_sub(point, inter->cy_hp);
		if (vector_compare(inter->cy_hp, inter->shape->data.cylinder.cap_s))
			normal = vector_scale(inter->shape->data.cylinder.normal, -1);
		else if (vector_compare(inter->cy_hp,
				inter->shape->data.cylinder.cap_e))
			normal = inter->shape->data.cylinder.normal;
	}
	else if (inter->shape->type == CONE)
		normal = cone_normal(inter);
	return (vector_normalize(normal));
}

// bool	check_unbound(t_ray *ray, t_hit *inter)
// {
// 	t_list	*unbound;
// 	t_shape	*shape;
// 	double	t;

// 	unbound = s()->unbound;
// 	while (unbound)
// 	{
// 		shape = (t_shape *)unbound->content;
// 		if (shape->type == PLANE)
// 		{
// 			if (inter_real_plane(&shape->data.plane, ray, &t) 
//				&& t < inter->distance)
// 			{
// 				inter->distance = t;
// 				inter->shape = shape;
// 				inter->check_hit = true;
// 			}
// 		}
// 		unbound = unbound->next;
// 	}
// 	return (inter->check_hit);
// }

// t_color	color_from_hex(unsigned int hex)
// {
// 	t_color	color;

// 	color.red = ((hex >> 24) & 0xFF) / 255.0;
// 	color.green = ((hex >> 16) & 0xFF) / 255.0;
// 	color.blue = ((hex >> 8) & 0xFF) / 255.0;
// 	color.alpha = ((hex >> 0) & 0xFF) / 255.0;
// 	return (color);
// }

/**
 * @brief Check whether the ray is intersecting with any shapes and
 * find the closest intersect point.
 * Main step:
 * 		1-get the closest inter point (tmp)
 * 		2-compare distance of tmp with closest(INFINITY), 
 * 			if tmp is closer update the closest point data and return, 
 * 			if not, continue to next shape.
 * 		Go through all shapes and update the closest point then return.s
 * 
 * @param shape Get current shape
 * @param tmp The tmp cloeset intersected point
 */
bool	check_intersection(t_fclass *shapes, t_ray *ray, t_hit *closest)
{
	int		i;
	t_shape	*shape;
	t_hit	tmp;
	double	checker;

	i = -1;
	if (!shapes)
		return (false);
	tmp = init_hit();
	if (s()->bvh)
		tmp.check_hit |= check_bvh_intersection(ray, s()->bvh, &tmp);
	// tmp.check_hit |= check_unbound(ray, &tmp);
	if (!tmp.check_hit && s()->shape_nbr[PLANE] == 0)
		return (false);
	while (++i < shapes->size)
	{
		shape = shapes->array[i];
		// if (shape->type == PLANE)
		// 	printf("before shape width: %d\n", shape->checkerboard->width);
		if (!is_intersect(shape, ray, &tmp, &checker))
			continue ;
		if (tmp.distance >= closest->distance)
			continue ;
		*closest = tmp;
		closest->ray = *ray;
		closest->shape = shape;
		// if (closest->shape->type == PLANE)
		// 	printf("before shape u_axis x: %f, y: %f, z: %f\nv_axis x: %f, y: %f, z: %f\n",
		// shape->u_axis.x, shape->u_axis.y, shape->u_axis.z, shape->v_axis.x, shape->v_axis.y, shape->v_axis.z);
		closest->hit_point = point_on_ray(ray, closest->distance);
		closest->hit_normal = get_normal(closest);
		// if (check_unbound(ray, &tmp))
		// 	break ;
	}
	return (closest->shape != NULL);
}
