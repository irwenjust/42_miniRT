/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:41:48 by likong            #+#    #+#             */
/*   Updated: 2025/01/08 14:27:51 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_shape	*copy_shape(t_shape *shape)
{
	t_shape	*res;

	res = ft_calloc(1, sizeof(t_shape));
	if (!res)
		return (NULL);
	res->id = shape->id;
	res->type = shape->type;
	res->shape_id[res->type] = shape->shape_id[shape->type];
	res->ks = shape->ks;
	res->shininess = shape->shininess;
	if (res->type == SPHERE)
	{
		res->data.sphere = shape->data.sphere;
		res->box = box_sphere(&(shape->data.sphere));
	}
	else if (res->type == PLANE)
		res->data.plane = shape->data.plane;
	else if (res->type == CYLINDER)
	{
		res->data.cylinder = shape->data.cylinder;
		res->box = box_cylinder(&(shape->data.cylinder));
	}
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
	{
		shape->data.sphere = *(t_sphere *)data;
		shape->box = box_sphere(&(shape->data.sphere));
	}
	else if (shape->type == PLANE)
	{
		shape->data.plane = *(t_plane *)data;
		shape->checkerboard = create_checkerboard(WHITE);
		s()->checkerboard = shape->checkerboard;
		s()->win.test = shape->checkerboard->img_ptr;
		printf("width: %d\n", shape->checkerboard->width);
	}
	else if (shape->type == CYLINDER)
	{
		shape->data.cylinder = *(t_cylinder *)data;
		shape->box = box_cylinder(&(shape->data.cylinder));
	}
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
	// printf("min x: %lf, y: %lf, z: %lf; max x: %lf, y: %lf, z: %lf\n", shape->box.min.x, shape->box.min.y, shape->box.min.z, shape->box.max.x, shape->box.max.y, shape->box.max.z);
}

void	rotate_shape(t_key *keys, t_shape *shape)
{
	if (shape->type == PLANE)
		rotate_plane(keys, &(shape->data.plane));
	else if (shape->type == CYLINDER)
	{
		rotate_cylinder(keys, &(shape->data.cylinder));
		shape->box = box_cylinder(&(shape->data.cylinder));
		// shape->box = shape->data.cylinder.box;
	}
}

//might need add scale_shape function soon
