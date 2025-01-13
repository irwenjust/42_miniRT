/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:38:26 by likong            #+#    #+#             */
/*   Updated: 2025/01/13 13:44:41 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	uv_repeat_wrap(double *u, double *v, int repeat)
{
	*u *= repeat;
	*v *= repeat;
	// printf("u: %f, v: %f\n", *u, *v);
	*u = fmod(*u, 1.0);
	*v = fmod(*v, 1.0);
	if (*u < 0)
		*u += 1.0;
	if (*v < 0)
		*v += 1.0;
}

static void	plane_uv(t_hit *hit, double *u, double *v, int repeat)
{
	t_vector	u_axis;
	t_vector	v_axis;
	t_vector	local_point;

	local_point = vector_sub(hit->hit_point, hit->shape->data.plane.center);
	// printf("u: %f, v: %f\n", *u, *v);
	u_axis = hit->shape->u_axis;
	v_axis = hit->shape->v_axis;
	// printf("after x: %f, y: %f, z: %f\n", u_axis.x, u_axis.y, u_axis.z);
	*u = vector_dot(u_axis, local_point) * 0.01;
	*v = vector_dot(v_axis, local_point) * 0.01;
	// printf("u: %f, v: %f\n", *u, *v);
	uv_repeat_wrap(u, v, repeat);
}

static void	sphere_uv(t_hit *hit, double *u, double *v, int repeat)
{
	t_vector	local_point;
	t_shape		*shape;
	double		azimuth;
	double		polar;

	shape = hit->shape;
	local_point = hit->hit_normal;
	local_point = (t_vector){
		vector_dot(local_point, shape->u_axis),
		vector_dot(local_point, shape->data.sphere.normal),
		vector_dot(local_point, shape)};
}

void	add_uv_axis(t_shape *shape, t_vector normal)
{
	t_vector	u_axis;
	t_vector	v_axis;

	u_axis = vector_cross(normal, (t_vector){0, 1, 0});
	if (sqrt(vector_dot(u_axis, u_axis)) < 1e-6)
		u_axis = vector_cross(normal, (t_vector){1, 0, 0});
	u_axis = vector_normalize(u_axis);
	v_axis = vector_normalize(vector_cross(normal, u_axis));
	shape->u_axis = u_axis;
	shape->v_axis = v_axis;
}

static int	wrap_coordinate(int value, int max)
{
	value %= max;
	if (value < 0)
		value += max;
	return (value);
}

t_color	get_pixel(t_image img, int x, int y)
{
	uint8_t	*start;
	t_color	color;

	start = (uint8_t *)(img.data + (y * img.size_line) + (x * (img.bpp / 8)));
	color.red = (start[2]);
	color.green = (start[1]);
	color.blue = (start[0]);
	// printf("r: %d, g: %d, b: %d\n", color.red, color.green, color.blue);
	return (color);
}

t_color	uv_get_color(t_image *img, double u, double v)
{
	int	x;
	int	y;
	int	width;
	int	height;

	width = img->width - 1;
	height = img->height - 1;
	x = (int)(width * u);
	y = (int)(height * v);
	x = wrap_coordinate(x, width);
	y = wrap_coordinate(y, height);
	// printf("x: %d, y: %d, u: %lf, v: %lf\n", x, y, u, v);
	return (get_pixel(*img, x, y));
}

void	find_uv(t_hit *hit)
{
	double	u;
	double	v;
	t_shape	*tmp;

	u = 0.0;
	v = 0.0;
	tmp = hit->shape;
	if (tmp->type == PLANE)
		plane_uv(hit, &u, &v, 1);
	else if (tmp->type == SPHERE)
		sphere_uv(hit, &u, &v, 1);
	hit->u = u;
	hit->v = v;
	// printf("u: %f, v: %f\n", hit->u, hit->v);
}
