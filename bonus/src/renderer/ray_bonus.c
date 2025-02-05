

#include "miniRT_bonus.h"

/**
 * @brief Generate a ray starts from camera position to viewport point
 * Main steps:
 * 		1-calculate the viewport point offset to viewport original point,
 * 		2-map the viewport point to camera direction, relative coordinates,
 * 		3-add the viewport point to camera normalized coordinates
 * 		  to get the absolute position in 3D world,
 * 		4-set a normalized ray, start from camera
 * 		5-subtrat tmp by ray start point to get the vector from camera to
 * 		  viewport point, then normalized it to get its direction.
 * 
 * @param cur The normalized 3D coordinates of viewport point
 * @param horizontal The horizontal offset of current view point
 * @param vertical The vertival offset of current view point
 * @param tmp The tmp vector used in the operation
 * @param ray The ray from camera to view point
 */
t_ray	make_ray(t_vector cur)
{
	t_vector	horizontal;
	t_vector	vertical;
	t_vector	tmp;
	t_ray		ray;

	horizontal = vector_scale(s()->normal_w, cur.x * s()->view_w);
	vertical = vector_scale(s()->normal_h, cur.y * s()->view_h);
	tmp = vector_add(vertical, horizontal);
	tmp = vector_add(tmp, s()->camera.normal);
	tmp = vector_add(tmp, s()->camera.coordinate);
	ray.start = s()->camera.coordinate;
	ray.normal = vector_normalize(vector_sub(tmp, ray.start));
	ray.inv_start = (t_vector){1.0 / ray.normal.x,
		1.0 / ray.normal.y, 1.0 / ray.normal.z};
	return (ray);
}

/**
 * @brief Calculate a point along ray based on a given distance
 * the equation is R(t) = O + tD
 */
inline t_vector	point_on_ray(t_ray *ray, double t)
{
	return (vector_add(ray->start, vector_scale(ray->normal, t)));
}

void	get_illumination_param(t_hit *hit)
{
	hit->refra_idx = hit->shape->refra_idx;
	hit->refractivity = 1 - hit->shape->ks;
	hit->depth = hit->shape->depth;
	if (hit->shape->ks > 0 && hit->shape->transparency == 0)
        hit->reflectance = hit->shape->ks;
    else if (hit->shape->ks > 0 && hit->shape->transparency > 0)
        hit->reflectance = calculate_fresnel(hit);
    else
	{
        hit->reflectance = 0.0;
	}
	hit->transmission = hit->shape->transparency * hit->refractivity * (1.0 - hit->reflectance);
}

void	add_color_by_refra(t_ray *ray, t_hit *closest, t_hit new_hit)
{
	t_vector	incident_dir;
	t_vector	normal;
	double		cos_theta;
	double		ratio;
	double		reflectance;
	
	incident_dir = vector_normalize(ray->normal);
	normal = (closest->side == OUTSIDE) 
					? closest->hit_normal 
					: vector_scale(closest->hit_normal, -1.0);
	cos_theta = fabs(vector_dot(incident_dir, normal));

	// 获取菲涅尔反射率
	ratio = (closest->side == OUTSIDE) 
					? (1.0 / closest->refra_idx) 
					: closest->refra_idx;
	reflectance = fmax(calculate_reflectance(cos_theta, 1.0, ratio), 0.1);

	// 能量守恒混合：反射颜色 * 反射率 + 折射颜色 * 透射率
	closest->color = add_color(
		closest->color,
		multi_color(new_hit.color, (1.0 - reflectance) * closest->refractivity)
	);

}

void	ray_tracer(t_ray *ray, t_hit *hit)
{
	t_ray new_ray;
	t_hit new_hit;

	if (!check_intersection(s()->shapes, ray, hit))
		return ;
	get_illumination_param(hit);
	phong_illumination(hit);
	if (hit->depth <= 0)
		return ;
	new_hit = generate_hit();
	if(hit->reflectance > 0.01)
	{
		set_reflection_ray(ray, &new_ray, hit, &new_hit);
		// ray_tracer(&new_ray, &new_hit);
		add_reflect_color(hit, &new_hit);
	}
	if (hit->shape->transparency > 0)
	{
		set_refraction_ray(ray, &new_ray, hit, &new_hit);
		check_refraction(&new_ray, hit);
		// ray_tracer(&new_ray, &new_hit);
		add_refract_color(hit, &new_hit);
	}
	if (hit->reflectance > 0.01 || hit->shape->transparency > 0)
	{
		ray_tracer(&new_ray, &new_hit);
		add_color_by_refra(ray, hit, new_hit);
	}
}

// void	ray_tracer(t_ray *ray, t_hit *hit)
// {
// 	t_ray reflect_ray;
// 	t_hit reflect_hit;
// 	t_ray refract_ray;
// 	t_hit refract_hit;

// 	if (!check_intersection(s()->shapes, ray, hit))
// 		return ;
// 	get_illumination_param(hit);
// 	phong_illumination(hit);
// 	if (hit->depth <= 0)
// 		return ;
// 	if(hit->reflectance > 0.01)
// 	{
// 		reflect_hit = generate_hit();
// 		set_reflection_ray(ray, &reflect_ray, hit, &reflect_hit);
// 		ray_tracer(&reflect_ray, &reflect_hit);
// 		add_reflect_color(hit, &reflect_hit);
// 	}
// 	if (hit->shape->transparency > 0)
// 	{
// 		refract_hit = generate_hit();
// 		set_refraction_ray(ray, &refract_ray, hit, &refract_hit);
// 		check_refraction(&refract_ray, hit);
// 		ray_tracer(&refract_ray, &refract_hit);
// 		add_refract_color(hit, &refract_hit);
// 	}
// }
