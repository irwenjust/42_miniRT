/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:02:38 by likong            #+#    #+#             */
/*   Updated: 2025/02/05 15:20:13 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

double	get_reflectance(double cos_theta, double ratio)
{
	double	res;

	res = (1.0 - ratio) / (1.0 + ratio);
	res = res * res;
	return (res + (1.0 - res) * pow((1.0 - cos_theta), 5.0));
}

// void	add_color_by_refra(t_ray *ray, t_hit *closest, t_hit new_hit)
// {
// 	t_vector	incident_dir;
// 	t_vector	normal;
// 	double		cos_theta;
// 	double		ratio;
// 	double		reflectance;
	
// 	incident_dir = vector_normalize(ray->normal);
// 	normal = (closest->side == OUTSIDE) 
// 					? closest->hit_normal 
// 					: vector_scale(closest->hit_normal, -1.0);
// 	cos_theta = fabs(vector_dot(incident_dir, normal));

// 	// 获取菲涅尔反射率
// 	ratio = (closest->side == OUTSIDE) 
// 					? (1.0 / closest->refra_idx) 
// 					: closest->refra_idx;
// 	reflectance = fmax(calculate_reflectance(cos_theta, 1.0, ratio), 0.1);

// 	// 能量守恒混合：反射颜色 * 反射率 + 折射颜色 * 透射率
// 	closest->color = add_color(
// 		closest->color,
// 		multi_color(new_hit.color, (1.0 - reflectance) * closest->refractivity)
// 	);

// }

void add_refract_color(t_hit *hit, t_hit *refract_hit)
{
	hit->color = add_color(
			multi_color(hit->color, hit->reflectance),
			multi_color(refract_hit->color, hit->transmission)
		);
	// printf("fle: %lf, fra: %lf\n", hit->reflectance, hit->transmission);
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
	cannot_TIR = (ratio * sqrt(1.0 - cos_theta * cos_theta) > 1.0);
	if (cannot_TIR || calculate_reflectance(cos_theta, 1.0, ratio) > ft_rand())
	{
		ray->normal = vector_normalize(vector_sub(ray->normal,
			vector_scale(hit->hit_normal, 2.0 * vector_dot(ray->normal, hit->hit_normal))));
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

void	set_refraction_ray(t_ray *ray, t_ray *refract_ray, t_hit *hit, t_hit *refract_hit)
{
	t_vector	offset;
	
	refract_hit->depth = hit->depth - 1;
	double	offset_scale = 1e-8;
	if (hit->side == OUTSIDE)
		offset = vector_scale(hit->hit_normal, offset_scale);
	else
		offset = vector_scale(hit->hit_normal, -offset_scale);
	refract_ray->start = vector_add(hit->hit_point, offset);
	refract_ray->normal = ray->normal;
	refract_ray->inv_start = (t_vector){1.0 / refract_ray->normal.x,
		1.0 / refract_ray->normal.y, 1.0 / refract_ray->normal.z};
}

void	check_refraction(t_ray *ray, t_hit *hit)
{
	double	ratio;
	
	if (vector_dot(hit->hit_normal, ray->normal) < 0.0)
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

// double	get_reflectance(double cos_theta, double ratio)
// {
// 	double	res;

// 	res = (1.0 - ratio) / (1.0 + ratio);
// 	res = res * res;
// 	return (res + (1.0 - res) * pow((1.0 - cos_theta), 5.0));
// }

// // void	add_color_by_refra(t_ray *ray, t_hit *closest, t_hit new_hit)
// // {
// // 	t_vector	incident_dir;
// // 	t_vector	normal;
// // 	double		cos_theta;
// // 	double		ratio;
// // 	double		reflectance;
	
// // 	incident_dir = vector_normalize(ray->normal);
// // 	normal = (closest->side == OUTSIDE) 
// // 					? closest->hit_normal 
// // 					: vector_scale(closest->hit_normal, -1.0);
// // 	cos_theta = fabs(vector_dot(incident_dir, normal));

// // 	// 获取菲涅尔反射率
// // 	ratio = (closest->side == OUTSIDE) 
// // 					? (1.0 / closest->refra_idx) 
// // 					: closest->refra_idx;
// // 	reflectance = fmax(get_reflectance(cos_theta, ratio), 0.1);

// // 	// 能量守恒混合：反射颜色 * 反射率 + 折射颜色 * 透射率
// // 	closest->color = add_color(
// // 		multi_color(closest->color, reflectance),
// // 		multi_color(new_hit.color, (1.0 - reflectance) * closest->refractivity)
// // 	);
// // }

// static void	get_refraction(t_ray *ray, t_hit *hit, double ratio)
// {
// 	t_vector	normal;
// 	t_vector	perp;
// 	t_vector	para;
// 	double		cos_theta;
// 	bool		cannot_TIR;
// 	// static int	count = 0;
	
// 	if (hit->side == OUTSIDE)
// 		normal = hit->hit_normal;
// 	else
// 		normal = vector_scale(hit->hit_normal, -1.0);
// 	cos_theta = fmin(vector_dot(vector_scale(ray->normal, -1.0), normal), 1.0);
// 	cannot_TIR = (ratio * sqrt(1.0 - cos_theta * cos_theta) > 1.0);
// 	if (cannot_TIR || get_reflectance(cos_theta, ratio) > ft_rand())
// 	{
// 		ray->normal = vector_normalize(vector_sub(ray->normal,
// 			vector_scale(hit->hit_normal, 2.0 * vector_dot(ray->normal, hit->hit_normal))));
// 		return ;
// 	}
// 	else
// 	{
// 		perp = vector_scale(vector_add(ray->normal,
// 			vector_scale(normal, cos_theta)), ratio);
// 		para = vector_scale(normal, -sqrt(fabs(1.0 - vector_dot(perp, perp))));
// 	}
// 	ray->normal = vector_normalize(vector_add(perp, para));
// }

// void	check_refraction(t_ray *ray, t_hit *hit)
// {
// 	double	ratio;
	
// 	if (vector_dot(hit->hit_normal, ray->normal) < 0.0)
// 		hit->side = OUTSIDE;
// 	else
// 		hit->side = INSIDE;
// 	if (hit->side == INSIDE)
// 		ratio = hit->refra_idx;
// 	else
// 		ratio = 1.0 / hit->refra_idx;
// 	get_refraction(ray, hit, ratio);
// 	ray->normal = vector_normalize(ray->normal);
// }
