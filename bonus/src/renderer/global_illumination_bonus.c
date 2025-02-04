

#include "miniRT_bonus.h"

double	calculate_reflectance(double cos_theta, double n1, double n2)
{
	double	res;

	res = (n1 - n2) / (n1 + n2);
	res = res * res;
	return (res + (1.0 - res) * pow((1.0 - cos_theta), 5.0));
}

static double    calculate_fresnel(t_hit *hit)
{
	t_vector	incident_dir;
	t_vector	normal;
	double		cos_theta;
	double		reflectance;
	
	incident_dir = vector_normalize(hit->ray.normal);
	if (hit->side == OUTSIDE)
        normal = hit->hit_normal;
    else
    {
        normal = vector_scale(hit->hit_normal, -1.0);
    }
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
    hit.color = BACKGROUND;
	return (hit);
}

void global_illumination(t_ray *ray, t_hit *hit)
{
    double reflectance;
    
    if (hit->shape->ks > 0 && hit->shape->transparency == 0)
        reflectance = hit->shape->ks;
    else if (hit->shape->ks > 0 && hit->shape->transparency > 0)
        reflectance = calculate_fresnel(hit);
    else if (hit->shape->ks == 0.0 && hit->shape->transparency == 0)
        return ;
    else
        reflectance = 0.0;
    if (hit->depth > 0)
    {
        if(reflectance > 0)
        {
            check_reflection(ray, hit, reflectance);
        }
        if (hit->shape->transparency > 0)
        {
            check_refraction(ray, hit, reflectance);
        }
    }
}

