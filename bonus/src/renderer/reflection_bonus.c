/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:50:40 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:52:39 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static t_vector	vector_reflect(t_vector incident, t_vector normal)
{
	return (vector_sub(incident,
			vector_scale(normal, 2.0 * vector_dot(incident, normal))));
}

void	set_reflection_ray(t_ray *ray, t_ray *reflect_ray, t_hit *hit)
{
	t_vector	offset;
	t_vector	reflect_dir;
	double		offset_scale;

	offset_scale = 1e-8;
	offset = vector_scale(hit->normal, offset_scale);
	ft_bzero(reflect_ray, sizeof(t_ray));
	reflect_ray->start = vector_add(hit->hit_point, offset);
	reflect_dir = vector_reflect(ray->normal, hit->normal);
	reflect_ray->normal = vector_normalize(reflect_dir);
}

void	add_reflect_color(t_hit *hit, t_hit *reflect_hit)
{
	hit->color = add_color(
			multi_color(hit->color, 1.0 - hit->reflectance),
			multi_color(reflect_hit->color, hit->reflectance)
			);
}
