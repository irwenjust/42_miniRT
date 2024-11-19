/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:49:56 by likong            #+#    #+#             */
/*   Updated: 2024/10/24 10:12:52 by likong           ###   ########.fr       */
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
	if (res->type == SPHERE)
		res->data.sphere = shape->data.sphere;
	else if (res->type == PLANE)
		res->data.plane = shape->data.plane;
	else if (res->type == CYLINDER)
		res->data.cylinder = shape->data.cylinder;
	return (res);
}

t_shape	*new_shape(void *data, t_shape_type type, int id)
{
	t_shape	*shape;

	shape = ft_calloc(1, sizeof(t_shape));
	if (!shape)
		return (NULL);
	shape->id = id;
	shape->type = type;
	if (shape->type == PLANE)
		shape->data.plane = *(t_plane *)data;
	else if (shape->type == SPHERE)
		shape->data.sphere = *(t_sphere *)data;
	else if (shape->type == CYLINDER)
		shape->data.cylinder = *(t_cylinder *)data;
	return (shape);
}


