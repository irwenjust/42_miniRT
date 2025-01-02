
#include "miniRT_bonus.h"

//static bool	is_obscured(t_hit *closest)
//{
//	int		i;
//	t_ray	ray;
//	t_hit	tmp;
//	t_light	*light;
//	t_shape	*shape;
//	double	valid_t;

//	// Guess don't need to check light exist or not here
//	i = -1;
//	tmp = init_hit();
//	light = fclass_index(s()->light, 0);
//	ray.start = vector_add(closest->hit_point, VEC_MIN);
//	ray.normal = vector_normalize(vector_sub(light->point, closest->hit_point));
//	tmp.distance = vector_magnitude(
//				vector_sub(light->point, closest->hit_point));
//	while (++i < s()->shapes->size)
//	{
//		shape = fclass_index(s()->shapes, i);
//		if (shape->id == closest->shape->id)
//			continue ;
//		// if (check_bvh_intersection(&ray, s()->bvh, &tmp) && tmp.distance <
//			// is_intersect(shape, &ray, &tmp) && 
//		// 	vector_magnitude(vector_sub(light->point, closest->hit_point)))
//		if (is_intersect(shape, &ray, &tmp, &valid_t) && tmp.distance 
//			< vector_magnitude(vector_sub(light->point, closest->hit_point)))
//			return (true);
//	}
//	return (false);
//}

static bool	is_obscured(t_hit *closest, t_ray *ray, double max_t)
{
	int		i;
	t_hit	tmp;
	t_shape	*shape;
	double	valid_t;

	i = -1;
	tmp = init_hit();
	while (++i < s()->shapes->size)
	{
		shape = fclass_index(s()->shapes, i);
		if (shape->id == closest->shape->id)
			continue ;
		// if (check_bvh_intersection(&ray, s()->bvh, &tmp) && tmp.distance <
			// is_intersect(shape, &ray, &tmp) && 
		// 	vector_magnitude(vector_sub(light->point, closest->hit_point)))
		if (is_intersect(shape, ray, &tmp, &valid_t) && tmp.distance < max_t)
			return (true);
	}
	return (false);
}

static bool	check_obscured(t_hit *closest)
{
	t_light		*light;
	t_vector	light_normal;
	t_ray		ray;
	double		light_distance;

	light = fclass_index(s()->light, 0);
	light_normal = vector_sub(light->point, closest->hit_point);
	light_distance = vector_magnitude(light_normal);
	ray.start = vector_add(closest->hit_point, VEC_MIN);
	ray.normal = vector_normalize(light_normal);
	return (is_obscured(closest, &ray, light_distance));
}

void	check_illumination(t_hit *closest)
{
	t_color	color;
	t_light	*light;

	light = fclass_index(s()->light, 0);
	if (!light)
	{
		ft_putstr_fd("Cannot find any light\n", 2); //exit??
		return ;
	}
	color = check_ambient(closest->color);
	if (!check_obscured(closest))
		color = add_color(color, diffuse(light, closest, light->brightness));
	closest->color = color;
}
