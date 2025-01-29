/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:48:31 by likong            #+#    #+#             */
/*   Updated: 2025/01/09 16:51:13 by likong           ###   ########.fr       */
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

void	ray_tracer(t_ray *ray, t_hit *closest)
{
	if (check_intersection(s()->shapes, &ray, &closest))
	{
		check_illumination(&closest);
		//check reflaction
		//check refraction
	}
	else
		return ;
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
