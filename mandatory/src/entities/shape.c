/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:49:56 by likong            #+#    #+#             */
/*   Updated: 2024/12/31 12:54:19 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_shape	*copy_shape(t_shape *shape)
{
	t_shape	*res;

	res = ft_calloc(1, sizeof(t_shape));
	if (!res)
		return (NULL);
	res->id = shape->id;
	res->type = shape->type;
	res->shape_id[res->type] = shape->shape_id[shape->type];
	if (res->type == SPHERE)
		res->data.sphere = shape->data.sphere;
	else if (res->type == PLANE)
		res->data.plane = shape->data.plane;
	else if (res->type == CYLINDER)
		res->data.cylinder = shape->data.cylinder;
	if (res->type != PLANE)
		res->box = shape_box(shape);
	return (res);
}

t_shape	*new_shape(void *data, t_shape_type type, int id, int shape_id)
{
	t_shape	*shape;

	shape = ft_calloc(1, sizeof(t_shape));
	if (!shape)
		return (NULL);
	shape->id = id;
	shape->type = type;
	shape->shape_id[type] = shape_id;
	if (shape->type == SPHERE)
		shape->data.sphere = *(t_sphere *)data;
	else if (shape->type == PLANE)
		shape->data.plane = *(t_plane *)data;
	else if (shape->type == CYLINDER)
		shape->data.cylinder = *(t_cylinder *)data;
	if (shape->type != PLANE)
		shape->box = shape_box(shape);
	return (shape);
}

void	move_shape(t_key *keys, t_shape *shape)
{
	if (shape->type == SPHERE)
	{
		move_sphere(keys, &(shape->data.sphere));
		shape->box = box_sphere(&(shape->data.sphere));
	}
	else if (shape->type == PLANE)
		move_plane(keys, &(shape->data.plane));
	else if (shape->type == CYLINDER)
	{
		move_cylinder(keys, &(shape->data.cylinder));
		shape->box = box_cylinder(&(shape->data.cylinder));
	}
	print_box(shape->box);
}

void	rotate_shape(t_key *keys, t_shape *shape)
{
	if (shape->type == PLANE)
		rotate_plane(keys, &(shape->data.plane));
	else if (shape->type == CYLINDER)
	{
		rotate_cylinder(keys, &(shape->data.cylinder));
		shape->box = box_cylinder(&(shape->data.cylinder));
	}
	print_box(shape->box);
}
