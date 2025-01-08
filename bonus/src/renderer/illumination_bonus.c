
#include "miniRT_bonus.h"

static bool	is_obscured(t_light *light, t_hit *closest)
{
	int		i;
	t_ray	ray;
	t_hit	tmp;
	t_shape	*shape;
	double	valid_t;

	i = -1;
	tmp = init_hit();
	ray.start = vector_add(closest->hit_point, VEC_MIN);
	ray.normal = vector_normalize(vector_sub(light->point, closest->hit_point));
	tmp.distance = vector_magnitude(
				vector_sub(light->point, closest->hit_point));
	while (++i < s()->shapes->size)
	{
		shape = fclass_index(s()->shapes, i);
		if (shape->id == closest->shape->id)
			continue ;
		// if (check_bvh_intersection(&ray, s()->bvh, &tmp) && tmp.distance <
			// is_intersect(shape, &ray, &tmp) && 
		// 	vector_magnitude(vector_sub(light->point, closest->hit_point)))
		if (is_intersect(shape, &ray, &tmp, &valid_t) && tmp.distance 
			< vector_magnitude(vector_sub(light->point, closest->hit_point)))
			return (true);
	}
	return (false);
}

void	check_illumination(t_hit *closest)
{
	t_color	color;
	// t_color	texture;
	t_color	final;
	t_light	*light;
	int		i;

	i = -1;
	// check_hit(closest);
	// texture = add_texture(closest);
	color = check_ambient(closest->color);
	// final = color_multi(color, texture);
	// if (closest->shape->type == PLANE)
	// 	final = texture;
	// else
		final = color;
	// final = check_ambient(closest->color);
	while (++i < s()->light->size)
	{
		light = fclass_index(s()->light, i);
		if (!light)
		{
			ft_putstr_fd("Cannot find any light\n", 2); //exit??
			return ;
		}
		if (!is_obscured(light, closest))
		{
			final = add_color(final, diffuse(light, closest, light->brightness));
			final = add_color(final, specular(light, closest, light->brightness));
		}
	}
	closest->color = final;
}
