/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:17:29 by likong            #+#    #+#             */
/*   Updated: 2025/02/17 11:41:32 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	is_obscured(t_light *light, t_hit *closest)
{
	int		i;
	t_ray	ray;
	t_hit	tmp;
	t_shape	*shape;
	double	valid_t;

	i = -1;
	tmp = init_hit();
	ray.start = vector_add(closest->hit_point, s()->vec_min);
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

void	check_hit_normal(t_hit *hit)
{
	if (hit->shape->type == PLANE)
		hit->hit_normal = hit->shape->data.plane.normal;
	if (vector_dot(hit->ray.normal, hit->hit_normal) > 0)
	{
		hit->check_hit = true;
		hit->hit_normal = vector_scale(hit->hit_normal, -1);
	}
}

void	check_hit(t_hit *hit)
{
	hit->hit_point = vector_add(hit->ray.start,
			vector_scale(hit->ray.normal, hit->distance));
	check_hit_normal(hit);
	//find_uv(hit);
}

void	check_illumination(t_hit *closest)
{
	t_color	color;
	t_light	*light;

	check_hit(closest);
	light = fclass_index(s()->light, 0);
	if (!light)
	{
		ft_putstr_fd("Cannot find any light\n", 2);
		return ;
	}
	color = check_ambient(closest->color);
	if (!is_obscured(light, closest))
		color = add_color(color, diffuse(light, closest, light->brightness));
	closest->color = color;
}
