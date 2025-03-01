/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_illumination_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:53:55 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/18 11:43:22 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static bool	is_obscured(t_light *light, t_hit *closest)
{
	int		i;
	t_ray	ray;
	t_hit	tmp;
	t_shape	*shape;

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
		if (is_intersect(shape, &ray, &tmp) && tmp.distance
			< vector_magnitude(vector_sub(light->point, closest->hit_point)))
			return (true);
	}
	return (false);
}

static t_color	diff(t_light *light, t_hit *inter, double brightness)
{
	t_vector	light_dir;
	t_color		color;
	double		cos_angle;
	double		diffuse_ratio;
	double		attenuation;

	light_dir = vector_sub(light->point, inter->hit_point);
	attenuation = fmin(1.0, 60.0 / vector_magnitude(light_dir));
	cos_angle = vector_cos(inter->normal, light_dir);
	diffuse_ratio = fmax(0.0, brightness * cos_angle * attenuation);
	color = multi_color(inter->color, diffuse_ratio);
	color = mix_color(color, light->color);
	return (color);
}

static t_color	spec(t_light *light, t_hit *inter, double brightness)
{
	t_vector	light_dir;
	t_vector	camera_dir;
	t_vector	half_vector;
	double		cos_angle;
	double		specular_ratio;

	if (inter->shape->shininess < 1.0)
		return (hex_to_color(BLACK));
	light_dir = vector_sub(light->point, inter->hit_point);
	camera_dir = vector_normalize(vector_scale(inter->ray.normal, -1));
	half_vector = vector_normalize(vector_add(camera_dir, light_dir));
	cos_angle = fmax(0.0, vector_dot(half_vector, inter->normal));
	specular_ratio = inter->shape->ks * brightness
		* pow(cos_angle, inter->shape->shininess);
	return (mix_color(multi_color(inter->color, specular_ratio), light->color));
}

static void	add_light_color(t_hit *hit, t_color *color, int i)
{
	t_light	*light;

	light = fclass_index(s()->light, i);
	if (!light)
		error_exit("cannot find any light");
	if (!is_obscured(light, hit))
	{
		*color = add_color(*color, diff(light, hit, light->brightness));
		*color = add_color(*color, spec(light, hit, light->brightness));
	}
}

void	phong_illumination(t_hit *closest)
{
	t_color	color;
	int		i;

	i = -1;
	check_hit(closest);
	check_bump(closest);
	if (closest->shape->cboard || closest->shape->tex)
		color = add_texture(closest);
	else
		color = closest->color;
	if (!closest->shape->tex)
		color = check_ambient(color);
	while (++i < s()->light->size)
		add_light_color(closest, &color, i);
	if (closest->shape->cboard || closest->shape->tex)
		color = mix_color(color, add_texture(closest));
	closest->color = color;
}
