/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:13:48 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/18 14:13:50 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	reset_camera(void)
{
	s()->camera = copy_camera(s()->ori_camera);
	init_viewport();
}

void	reset_lights(void)
{
	free(s()->light->array[0]);
	s()->light->array[0] = copy_light(s()->ori_light->array[0]);
}

static void	copy_shape_data(t_shape *shape, t_shape *ori)
{
	if (shape->type == SPHERE)
		shape->data.sphere = ori->data.sphere;
	else if (shape->type == PLANE)
		shape->data.plane = ori->data.plane;
	else if (shape->type == CYLINDER)
		shape->data.cylinder = ori->data.cylinder;
	if (shape->type != PLANE)
		shape->box = shape_box(shape);
}

void	reset_shapes(void)
{
	int	i;

	i = -1;
	while (++i < s()->shapes->size)
	{
		copy_shape_data(s()->shapes->array[i], s()->ori_shapes->array[i]);
	}
}

void	reset_all(void)
{
	s()->ambient = copy_ambient(s()->ori_ambient);
	reset_camera();
	reset_lights();
	reset_shapes();
}
