

#include "miniRT_bonus.h"

t_color	diffuse(t_light *light, t_hit *inter, double brightness)
{
	t_vector	light_dir;
	t_color		color;
	double		cos_angle;
	double		diffuse_ratio;
	double		attenuation;

	light_dir = vector_sub(light->point, inter->hit_point);
	attenuation = MIN(1.0, 60.0 / vector_magnitude(light_dir));
	cos_angle = vector_cos(inter->hit_normal, light_dir);
	diffuse_ratio = brightness * cos_angle * attenuation;
	color = add_bright_to_color(inter->color, diffuse_ratio);
	color = mix_color(color, light->color);
	return (color);
}