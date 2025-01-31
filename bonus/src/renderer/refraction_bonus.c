/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:02:38 by likong            #+#    #+#             */
/*   Updated: 2025/01/31 17:16:19 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static double	get_reflectance(double cos_theta, double ratio)
{
	double	res;

	res = (1.0 - ratio) / (1.0 + ratio);
	res = res * res;
	return (res + (1.0 - res) * pow((1.0 - cos_theta), 5.0));
}

static void	get_refraction(t_ray *ray, t_hit *hit, double ratio)
{
	t_vector	normal;
	t_vector	perp;
	t_vector	para;
	double		cos_theta;
	bool		cannot_TIR;
	// static int	count = 0;
	
	if (hit->side == OUTSIDE)
		normal = hit->hit_normal;
	else
		normal = vector_scale(hit->hit_normal, -1.0);
	cos_theta = fmin(vector_dot(vector_scale(ray->normal, -1.0), normal), 1.0);
	cannot_TIR = (ratio * sqrt(1.0 - cos_theta * cos_theta) > 0);
	// printf("TIR: %lf\n", ratio);
	if (cannot_TIR || get_reflectance(cos_theta, ratio) > ft_rand())
	{
		// printf("count: %d\n", ++count);
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
	
	ratio = 0.0;
	if (vector_dot(hit->hit_normal, ray->normal) > 0.0)
		hit->side = INSIDE;
	else
		hit->side = OUTSIDE;
	if (hit->side == INSIDE)
		hit->refract = 1.0 - hit->shape->ks;
	else
		hit->refract = 1.0 / (1.0 - hit->shape->ks);
	get_refraction(ray, hit, ratio);
}
