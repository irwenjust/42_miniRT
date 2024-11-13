/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:35:15 by yzhan             #+#    #+#             */
/*   Updated: 2024/11/13 16:35:18 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
t_vector	convert_viewport(double x, double y)
{
	t_vector	converted;

	converted.x = ((x / WIDTH) * 2.0f) - 1;
	converted.y = ((y / HEIGHT) * 2.0f) - 1;
	converted.z = 0;
	return (converted);
}
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
t_ray make_ray(t_vector cur)
{
	t_vector horizontal;
	t_vector vertical;
	t_vector tmp;
	t_ray ray;

	//vector from viewport (0) to current viewport point
	horizontal = vector_multiple(s()->normal_w, cur.x * s()->view_w);
	vertical = vector_multiple(s()->normal_h, cur.y * s()->view_h);
	tmp = vector_add(vertical, horizontal);
	//map viewport point to camera direction
	tmp = vector_add(tmp, s()->camera.normal);
	//add camera postion, now tmp is the point where ray will pass*/
	tmp = vector_add(tmp, s()->camera.coordinate);
	//the start point of ray is camera position
	ray.start = s()->camera.coordinate;
	//subtract tmp with start point to get the vector, then normalized it
	ray.direct = vector_normalize(vector_subtract(tmp, ray.start));
	return (ray);
}

/**
 * @brief Check whether the ray is intersecting with any shapes
 */
bool check_intersect(t_fclass *shapes, t_ray *ray, t_hit *closest)
{
	int i;
	t_shape *shape;
	t_hit	tmp;

	i = -1;
	if (!shapes)
		return (false);
	while (++i < shapes->size)
	{
		//check shapes one by one
		shape = shapes->array[i];
		if (!is_intersect(shape, ray, &tmp))
			continue ;
		*closest = tmp;
		closest->ray = *ray;
		closest->shape = shape;
		//NOT FINISHED
		
	}
	return (true);
}

/**
 * @brief Function to render the shapes and lights
 * Main steps:
 * 		1-convert 2D screen coodinates to 3D, 
 * 		2-make a ray from carema to viewpoint,
 * 		3-find the intersected point,
 * 		4-update the color and shadow of the closest intersected point
 * 		5-print the color on sreen.
 * 
 * @param cur The current 2D coordinates on screen
 * @param converted_cur The 3D coordinates converted from 2D cur
 * @param closest The closest intersect point
 * @param ray The ray from camera direct to current viewpoint
 */
void render()
{
	t_vector cur;
	t_vector converted_cur;
	t_hit closest;
	t_ray ray;

	cur.y = -1;
	while (++cur.y < HEIGHT)
	{
		cur.x = -1;
		while (++cur.x < WIDTH)
		{
			closest.color = BLACK;
			closest.shape = NULL;
			closest.distance = INFINITY;
		//1-3d coordinate of viewport
			converted_cur = convert_viewport(cur.x, cur.y);
		//2-ray from cerama to viewport
			ray = make_ray(converted_cur);
		//3-check whether the ray is intersect with shape
			check_intersect(s()->shapes, &ray, &closest);
		//4-if intersect, update closest color based on other env
			put_pixel(closest.color, cur.x, cur.y);
		}
	}
	mlx_put_image_to_window(s()->win.mlx, s()->win.disp, s()->win.img, 0, 0);
}
