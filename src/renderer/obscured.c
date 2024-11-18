/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obscured.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:17:29 by likong            #+#    #+#             */
/*   Updated: 2024/11/18 15:30:50 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	is_obscured(t_hit *closest)
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
	tmp.distance = INFINITY;
	tmp.shape = NULL;
	while (++i < s()->shapes->size)
	{
		shape = fclass_index(s()->shapes, i);
		if (shape->id == closest->shape->id)
			continue ;
		if (is_intersect(shape, &ray, &tmp) && tmp.distance <
			vector_len(vector_sub(light->point, closest->hit_point)))
			return (true);
	}
	return (false);
}
