/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination_tools_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:17:39 by likong            #+#    #+#             */
/*   Updated: 2025/02/17 14:21:54 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

double	calculate_reflectance(double cos_theta, double n1, double n2)
{
	double	res;

	res = (n1 - n2) / (n1 + n2);
	res = res * res;
	return (res + (1.0 - res) * pow((1.0 - cos_theta), 5.0));
}

double	calculate_fresnel(t_hit *hit)
{
	t_vector	incident_dir;
	t_vector	normal;
	double		cos_theta;
	double		reflectance;

	incident_dir = vector_normalize(hit->ray.normal);
	if (hit->side == OUTSIDE)
		normal = hit->normal;
	else
		normal = vector_scale(hit->normal, -1.0);
	cos_theta = fabs(vector_dot(incident_dir, normal));
	if (hit->side == OUTSIDE)
		reflectance = calculate_reflectance(cos_theta, 1.0, hit->refra_idx);
	else
	{
		reflectance = calculate_reflectance(cos_theta, hit->refra_idx, 1.0);
	}
	reflectance = fmax(reflectance, 0.1);
	return (reflectance);
}

t_hit	generate_hit(void)
{
	t_hit	hit;

	ft_bzero(&hit, sizeof(t_hit));
	hit.distance = INFINITY;
	hit.shape = NULL;
	hit.color = hex_to_color(BACKGROUND);
	return (hit);
}
