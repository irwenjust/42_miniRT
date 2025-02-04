#include "miniRT_bonus.h"

static t_vector vector_reflect(t_vector incident, t_vector normal)
{
    return vector_sub(incident, 
        vector_scale(normal, 2.0 * vector_dot(incident, normal)));
}

static void    set_reflection_ray(t_ray *ray, t_ray *reflect_ray, t_hit *hit)
{
    t_vector offset;
    t_vector reflect_dir;
    double    offset_scale = 1e-4;

    // 计算反射方向
    reflect_dir = vector_reflect(ray->normal, hit->hit_normal);
    
    // 添加法线偏移防止自相交
    offset = vector_scale(hit->hit_normal, offset_scale);
    reflect_ray->start = vector_add(hit->hit_point, offset);
    reflect_ray->normal = reflect_dir;
    reflect_ray->inv_start = (t_vector){1.0 / reflect_dir.x,
        1.0 / reflect_dir.y, 1.0 / reflect_dir.z};
}

void check_reflection(t_ray *ray, t_hit *hit, double reflectance)
{
    t_ray reflect_ray;
    t_hit reflect_hit;

    reflect_hit = generate_hit();
    set_reflection_ray(ray, &reflect_ray, hit);
    reflect_hit.depth = hit->depth - 1;
    ray_tracer(&reflect_ray, &reflect_hit);
    hit->color = add_color(
        multi_color(hit->color, 1.0 - reflectance),
        multi_color(reflect_hit.color, reflectance)
    );
}