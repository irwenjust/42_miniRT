/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:48:31 by likong            #+#    #+#             */
/*   Updated: 2025/02/02 15:43:21 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

/**
 * @brief 2D screen coordinates(x, y) into normalized 3D coordinates(x, y, z),
 * to centers the viewport at (0, 0).
 * And maps the screen dimensions to a range of [-1, 1] range for both x and y.
 * The range from -1 to 1 is 2, calculate the (x, y) relative position on screen,
 * and multipe coordinate with 2.0f to mapping coordinate to a range [0, 2],
 * then:
 * 		x = 0 ---> x = -1, the left edge of screen
 * 		x = WIDTH ---> x = 1, the right edge of screen
 * 		x = WIDTH / 2 ---> x = 0, the center of screen
 */
static t_vector	convert_viewport(double x, double y)
{
	t_vector	converted;

	converted.x = ((x * INVWIDTH) * 2.0f) - 1;
	converted.y = ((y * INVHEIGHT) * 2.0f) - 1;
	converted.z = 0;
	return (converted);
}

void	put_pixel(t_color c, int x, int y)
{
	char	*dst;

	dst = s()->win.addr + (y * WIDTH + x) * (int)(s()->win.bpp * 0.125);
	*(unsigned int *)dst = (c.alpha << 24 | c.red << 16 | c.green << 8 | c.blue);
}

static t_hit	generate_hit(void)
{
	t_hit	new_hit;

	ft_bzero(&new_hit, sizeof(t_hit));
	new_hit.distance = INFINITY;
	new_hit.shape = NULL;
	return (new_hit);
}

void	set_hit_ray(t_ray *ray, t_ray *new_ray, t_hit *closest, t_hit *new_hit)
{
	t_vector	offset;
	
	new_hit->depth = closest->depth - 1;
	double	offset_scale = 1e-4;
	if (closest->side == OUTSIDE)
		offset = vector_scale(closest->hit_normal, offset_scale);
	else
		offset = vector_scale(closest->hit_normal, -offset_scale);
	new_ray->start = vector_add(closest->hit_point, offset);
	new_ray->normal = ray->normal;
	new_ray->inv_start = (t_vector){1.0 / new_ray->normal.x,
		1.0 / new_ray->normal.y, 1.0 / new_ray->normal.z};
}

void	ray_tracer(t_ray *ray, t_hit *closest)
{
	// t_ray	new_ray;
	// t_hit	new_hit;
	
	if (!check_intersection(s()->shapes, ray, closest))
		return ;
	//check reflection
	if (!closest || !closest->shape)
		return ;
	closest->refractivity = 1 - closest->shape->ks;
	closest->refra_idx = closest->shape->refra_idx;
	closest->depth = closest->shape->depth;
	check_illumination(closest);
	if (closest->depth <= 0)
		return ;
	if (closest->depth > 0 && closest->refractivity > 0)
	{
		// new_hit = generate_hit();
		// set_hit_ray(ray, &new_ray, closest, &new_hit);
		// check_refraction(&new_ray, closest);
	
		// ray_tracer(&new_ray, &new_hit);
		// add_color_by_refra(ray, closest, new_hit);
		if (closest->shape->ks > 0) // 如果物体有镜面反射
		{
			t_ray	reflected_ray;
			t_hit	reflected_hit = generate_hit();
			// 计算反射方向
			reflected_ray.start = vector_add(closest->hit_point,
				vector_scale(closest->hit_normal, 1e-4)); // 避免自相交
			reflected_ray.normal = vector_normalize(vector_sub(ray->normal,
				vector_scale(closest->hit_normal, 2.0 * vector_dot(ray->normal, closest->hit_normal))));

			// 递归追踪反射光线
			ray_tracer(&reflected_ray, &reflected_hit);

			// 计算菲涅尔反射率（已计算）
			double reflectance = fmax(get_reflectance(fabs(vector_dot(ray->normal, closest->hit_normal)), closest->refra_idx), 0.1);

			// 混合颜色
			closest->color = add_color(
				multi_color(closest->color, (1.0 - reflectance) * closest->refractivity), // 折射部分
				multi_color(reflected_hit.color, reflectance * closest->shape->ks) // 反射部分
			);
		}
	}
	
}

void	*fake_render_thread(void *arg)
{
	t_thread_data	*data;
	t_hit		closest;
	t_vector	cur;
	t_vector	converted_cur;
	t_ray		ray;

	data = (t_thread_data *)arg;
	cur.y = data->start_y;
	while (cur.y < data->end_y)
	{
		cur.x = data->start_x;
		while (cur.x < data->end_x)
		{
			closest = init_hit(); //default color is BLACK, set a background color?
			converted_cur = convert_viewport(cur.x, cur.y);
			ray = make_ray(converted_cur);
			// if (check_intersection(s()->shapes, &ray, &closest))
			// 	check_illumination(&closest);
			ray_tracer(&ray, &closest);
			put_pixel(closest.color, cur.x, cur.y);
			cur.x += 3;
		}
		cur.y += 3;
	}
	return (NULL);
}

void	*render_thread(void *arg)
{
	t_thread_data	*data;
	t_hit		closest;
	t_vector	cur;
	t_vector	converted_cur;
	t_ray		ray;

	data = (t_thread_data *)arg;
	cur.y = data->start_y;
	while (cur.y < data->end_y)
	{
		cur.x = data->start_x;
		while (cur.x < data->end_x)
		{
			closest = init_hit();
			converted_cur = convert_viewport(cur.x, cur.y);
			ray = make_ray(converted_cur);
			// if (check_intersection(s()->shapes, &ray, &closest))
			// 	check_illumination(&closest);
			ray_tracer(&ray, &closest);
			put_pixel(closest.color, cur.x, cur.y);
			cur.x++;
		}
		cur.y++;
	}
	return (NULL);
}

/**
 * @brief Function to render the shapes and lights
 * Main steps:
 * 		1-convert 2D screen coodinates to 3D, 
 * 		2-make a ray from carema to viewpoint,
 * 		3-find the intersected point,
 * 		TODO 4-update the color and shadow of the closest intersected point
 * 		5-print the color on sreen.
 * 
 * @param cur The current 2D coordinates on screen
 * @param converted_cur The 3D coordinates converted from 2D cur
 * @param closest The closest intersect point
 * @param ray The ray from camera direct to current viewpoint
 */
void	render(int fake)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	data[NUM_THREADS];
	int				i;

	i = 0;
	while (i < NUM_THREADS)
	{
		data[i].start_x = 0;
		data[i].end_x = WIDTH;
		data[i].start_y = i * (HEIGHT / NUM_THREADS);
		data[i].end_y = (i + 1) * (HEIGHT / NUM_THREADS);
		if (fake == 0)
			pthread_create(&threads[i], NULL, render_thread, &data[i]);
		else
			pthread_create(&threads[i], NULL, fake_render_thread, &data[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	mlx_put_image_to_window(s()->win.mlx, s()->win.disp, s()->win.img, 0, 0);
	display_menu();
}
