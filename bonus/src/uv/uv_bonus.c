/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:38:26 by likong            #+#    #+#             */
/*   Updated: 2025/02/17 15:44:52 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static int	wrap_coordinate(int value, int max)
{
	value %= max;
	if (value < 0)
		value += max;
	return (value);
}

void	uv_repeat_wrap(double *u, double *v, int repeat)
{
	*u *= repeat;
	*v *= repeat;
	*u = fmod(*u, 1.0);
	*v = fmod(*v, 1.0);
	if (*u < 0)
		*u += 1.0;
	if (*v < 0)
		*v += 1.0;
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
	else if (tmp->type == CYLINDER)
		cylinder_uv(hit, &u, &v, 1);
	else if (tmp->type == CONE)
		cone_uv(hit, &u, &v, 1);
	hit->u = u;
	hit->v = v;
}
