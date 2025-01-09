/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:41:48 by likong            #+#    #+#             */
/*   Updated: 2025/01/09 16:12:30 by likong           ###   ########.fr       */
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
	res->u_axis = shape->u_axis;
	res->v_axis = shape->v_axis;
	res->checkerboard = shape->checkerboard;
	if (res->type == SPHERE)
		res->data.sphere = shape->data.sphere;
	else if (res->type == PLANE)
		res->data.plane = shape->data.plane;
	else if (res->type == CYLINDER)
		res->data.cylinder = shape->data.cylinder;
	else if (res->type == CONE)
		res->data.cone = shape->data.cone;
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
	{
		shape->data.plane = *(t_plane *)data;
		shape->checkerboard = create_checkerboard(WHITE);
		s()->checkerboard = shape->checkerboard;
		s()->win.test = shape->checkerboard->img_ptr;
	}
	else if (shape->type == CYLINDER)
		shape->data.cylinder = *(t_cylinder *)data;
	else if (shape->type == CONE)
		shape->data.cone = *(t_cone *)data;
	if (shape->type != PLANE)
		shape->box = shape_box(shape);
	printf("shape type: %i\n", shape->type);
	print_box(shape->box);
	return (shape);
}

void	move_shape(t_key *keys, t_shape *shape)
{
	if (shape->type == SPHERE)
	{
		move_sphere(keys, &(shape->data.sphere));
		// shape->box = box_sphere(&(shape->data.sphere));
		// shape->box = shape->data.sphere.box;
	}
	else if (shape->type == PLANE)
		move_plane(keys, &(shape->data.plane));
	else if (shape->type == CYLINDER)
	{
		move_cylinder(keys, &(shape->data.cylinder));
		// shape->box = box_cylinder(&(shape->data.cylinder));
		// shape->box = shape->data.cylinder.box;
	}
	else if (shape->type == CONE)
		move_cone(keys, &(shape->data.cone));
	if (shape->type != PLANE)
		shape->box = shape_box(shape);
	print_box(shape->box);
}

void	rotate_shape(t_key *keys, t_shape *shape)
{
	if (shape->type == PLANE)
		rotate_plane(keys, &(shape->data.plane));
	else if (shape->type == CYLINDER)
	{
		rotate_cylinder(keys, &(shape->data.cylinder));
		// shape->box = box_cylinder(&(shape->data.cylinder));
		// shape->box = shape->data.cylinder.box;
	}
	else if (shape->type == CONE)
		rotate_cone(keys, &(shape->data.cone));
	if (shape->type != PLANE)
		shape->box = shape_box(shape);
	print_box(shape->box);
}

//might need add scale_shape function soon
