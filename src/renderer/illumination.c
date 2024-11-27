/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:17:29 by likong            #+#    #+#             */
/*   Updated: 2024/11/27 20:10:45 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	is_obscured(t_hit *closest)
{
	int		i;
	t_ray	ray;
	t_hit	tmp;
	t_light	*light;
	t_shape	*shape;
	
	// Guess don't need to check light exist or not here
	light = fclass_index(s()->light, 0);
	ray.start = vector_add(closest->hit_point, VEC_MIN);
	ray.normal = vector_normalize(vector_sub(light->point, closest->hit_point));
	i = -1;
	tmp = init_hit();
	tmp.distance = vector_magnitude(vector_sub(light->point, closest->hit_point));
	// tmp.distance = INFINITY;
	// tmp.shape = NULL;
	while (++i < s()->shapes->size)
	{
		shape = fclass_index(s()->shapes, i);
		if (shape->id == closest->shape->id)
			continue ;
		if (is_intersect(shape, &ray, &tmp) && tmp.distance <
			vector_magnitude(vector_sub(light->point, closest->hit_point)))
			return (true);
	}
	return (false);
}

void	check_illumination(t_hit *closest)
{
	t_color	color;
	t_light	*light;

	light = fclass_index(s()->light, 0);
	if (!light)
	{
		ft_putstr_fd("Cannot find any light\n", 2);
		return ;
	}
	color = check_ambient(closest->color);
	if (!is_obscured(closest))
		color = add_color(color, diffuse(light, closest, light->brightness));
	closest->color = color;
}
