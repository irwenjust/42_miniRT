/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_tool_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:07:58 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:08:02 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static t_vector	find_shape_type(t_shape *shape)
{
	if (shape->type == SPHERE)
		return (shape->data.sphere.center);
	else if (shape->type == PLANE)
		return (shape->data.plane.center);
	else if (shape->type == CYLINDER)
		return (shape->data.cylinder.center);
	else if (shape->type == CONE)
		return (shape->data.cone.center);
	return ((t_vector){0});
}

static double	find_vec(t_shape *shape, int axis)
{
	if (axis == X)
		return (find_shape_type(shape).x);
	else if (axis == Y)
		return (find_shape_type(shape).y);
	return (find_shape_type(shape).z);
}

int	split_box(int axis, t_shape **shapes, int amount)
{
	int		i;
	int		j;
	double	mid;
	t_shape	*tmp;

	i = 0;
	j = amount - 1;
	mid = find_vec(shapes[(int)(amount * 0.5)], axis);
	while (i <= j)
	{
		while (i >= 0 && find_vec(shapes[i], axis) < mid)
			i++;
		while (j >= 0 && find_vec(shapes[j], axis) >= mid)
			j--;
		if (i < j)
		{
			tmp = shapes[i];
			shapes[i] = shapes[j];
			shapes[j] = tmp;
		}
	}
	return (i);
}

int	find_max_axis(t_aabb box)
{
	t_vector	direction;

	direction = vector_sub(box.max, box.min);
	direction.x = fabs(direction.x);
	direction.y = fabs(direction.y);
	direction.z = fabs(direction.z);
	if (direction.x >= direction.y && direction.x >= direction.z)
		return (X);
	else if (direction.y >= direction.x && direction.y >= direction.z)
		return (Y);
	return (Z);
}

t_aabb	generate_box(t_shape **shapes, int amount)
{
	int		i;
	t_aabb	box;
	t_shape	*shape;

	i = -1;
	box.min = (t_vector){INFINITY, INFINITY, INFINITY};
	box.max = (t_vector){-INFINITY, -INFINITY, -INFINITY};
	while (++i < amount)
	{		
		shape = shapes[i];
		if (shape->type != PLANE)
		{
			box.min = vector_min(box.min, shape->box.min);
			box.max = vector_max(box.max, shape->box.max);
		}
	}
	return (box);
}
