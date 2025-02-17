/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:02:38 by likong            #+#    #+#             */
/*   Updated: 2025/02/17 14:22:20 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	add_refract_color(t_hit *hit, t_hit *refract_hit)
{
	hit->color = add_color(
			multi_color(hit->color, hit->reflectance),
			multi_color(refract_hit->color, hit->transmission)
			);
}

static void	get_refraction(t_ray *ray, t_hit *hit, double ratio)
{
	t_vector	normal;
	t_vector	perp;
	t_vector	para;
	double		cos_theta;
	bool		cannot_tir;

	if (hit->side == OUTSIDE)
		normal = hit->normal;
	else
		normal = vector_scale(hit->normal, -1.0);
	cos_theta = fmin(vector_dot(vector_scale(ray->normal, -1.0), normal), 1.0);
	cannot_tir = (ratio * sqrt(1.0 - cos_theta * cos_theta) > 1.0);
	if (cannot_tir || calculate_reflectance(cos_theta, 1.0, ratio) > ft_rand())
	{
		ray->normal = vector_normalize(vector_sub(ray->normal, vector_scale
					(hit->normal, 2.0 * vector_dot(ray->normal, hit->normal))));
		return ;
	}
	else
	{
		perp = vector_scale(vector_add(ray->normal,
					vector_scale(normal, cos_theta)), ratio);
		para = vector_scale(normal, -sqrt(fabs(1.0 - vector_dot(perp, perp))));
	}
	ray->normal = vector_normalize(vector_add(perp, para));
}

void	check_refraction(t_ray *ray, t_hit *hit)
{
	double	ratio;

	if (vector_dot(hit->normal, ray->normal) < 0.0)
		hit->side = OUTSIDE;
	else
		hit->side = INSIDE;
	if (hit->side == INSIDE)
		ratio = hit->refra_idx;
	else
		ratio = 1.0 / hit->refra_idx;
	get_refraction(ray, hit, ratio);
	ray->normal = vector_normalize(ray->normal);
}

void	set_refraction_ray(t_ray *ray, t_ray *refract_ray, t_hit *hit)
{
	t_vector	offset;
	double		offset_scale;

	offset_scale = 1e-8;
	if (hit->side == OUTSIDE)
		offset = vector_scale(hit->normal, offset_scale);
	else
		offset = vector_scale(hit->normal, -offset_scale);
	ft_bzero(refract_ray, sizeof(t_ray));
	refract_ray->start = vector_add(hit->hit_point, offset);
	refract_ray->normal = ray->normal;
	refract_ray->inv_start = (t_vector){1.0 / refract_ray->normal.x,
		1.0 / refract_ray->normal.y, 1.0 / refract_ray->normal.z};
	check_refraction(refract_ray, hit);
}
