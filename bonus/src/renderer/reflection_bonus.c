

#include "miniRT_bonus.h"

void set_reflection_ray(t_ray *ray, t_ray *new_ray, t_hit *closest, t_hit *new_hit)
{
    t_vector offset;
    double offset_scale = 1e-4;

    new_hit->depth = closest->depth - 1;
    // 计算反射光线的方向
    t_vector incident = ray->normal;  // 入射光线的方向
    t_vector normal = closest->hit_normal;  // 表面法线
    double dot_product = vector_dot(incident, normal);  // 计算入射光线与法线的点积

    // 反射方向：I - 2 * (I · N) * N
    t_vector reflected_dir = vector_sub(incident, vector_scale(normal, 2 * dot_product));

    // 计算反射光线的起点，避免与表面重合
    if (closest->side == OUTSIDE)
        offset = vector_scale(normal, offset_scale);
    else
        offset = vector_scale(normal, -offset_scale);
    
    // 设置反射光线的起点和方向
    new_ray->start = vector_add(closest->hit_point, offset);
    new_ray->normal = reflected_dir;  // 反射光线的方向
    new_ray->inv_start = (t_vector){1.0 / new_ray->normal.x,
                                    1.0 / new_ray->normal.y, 
                                    1.0 / new_ray->normal.z};
}


void	check_reflection(t_ray *ray, t_hit *closest, t_hit *new_hit)
{
    t_ray	new_ray;

    set_reflection_ray(ray, &new_ray, closest, new_hit);
    if (!check_intersection(s()->shapes, &new_ray, new_hit))
        return ;
    if (!new_hit || !new_hit->shape)
        return ;
    check_illumination(new_hit);
    closest->color = add_color(
		closest->color,
		add_bright_to_color(new_hit->color, closest->shape->ks)
	);

}

void	add_color_by_reflect(t_hit *closest, t_hit new_hit)
{
    if (closest->shape->ks <= 0.0)
		return ;
    // 混合公式：最终颜色 += 反射颜色 * 材质反射系数 (ks)
    closest->color = add_color(
		closest->color,
		add_bright_to_color(new_hit.color, closest->shape->ks)
	);
}
