

#include "miniRT_bonus.h"

t_color	diffuse(t_light *light, t_hit *inter, double brightness)
{
	t_vector	light_dir;
	t_color		color;
	double		cos_angle;
	double		diffuse_ratio;
	double		attenuation;

	light_dir = vector_sub(light->point, inter->hit_point);
	attenuation = fmin(1.0, 60.0 / vector_magnitude(light_dir));
	cos_angle = vector_cos(inter->hit_normal, light_dir);
	diffuse_ratio = fmax(0.0, brightness * cos_angle * attenuation);
	color = add_bright_to_color(inter->color, diffuse_ratio);
	color = mix_color(color, light->color);
	return (color);
}

t_color specular(t_light *light, t_hit *inter, double brightness)
{
	t_vector	light_dir;
	t_vector	camera_dir;
	t_vector	half_vector;
	double		cos_angle;
	double		specular_ratio;

	if (inter->shape->shininess < 1.0)
		return (BLACK);
	light_dir = vector_sub(light->point, inter->hit_point);
	camera_dir = vector_normalize(vector_multi(inter->ray.normal, -1));
	half_vector = vector_normalize(vector_add(camera_dir, light_dir));
	cos_angle = fmax(0.0, vector_dot(half_vector, inter->hit_normal));
	specular_ratio = inter->shape->ks * brightness * pow(cos_angle, inter->shape->shininess);
	return (mix_color(add_bright_to_color(inter->color, specular_ratio), light->color));
}