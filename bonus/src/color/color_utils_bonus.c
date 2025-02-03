/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:33:24 by likong            #+#    #+#             */
/*   Updated: 2025/01/09 20:32:54 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_color	color_create(double r, double g, double b)
{
	t_color	color;

	color.red = r;
	color.green = g;
	color.blue = b;
	return (color);
}



t_color	*get_color(int type, int i)
{
	t_shape	*shape;
	t_color	*rgb;

	if (type == SHAPE)
	{
		shape = s()->shapes->array[i];
		if (shape->type == SPHERE)
			rgb = &shape->data.sphere.color;
		else if (shape->type == PLANE)
			rgb = &shape->data.plane.color;
		else if (shape->type == CYLINDER)
			rgb = &shape->data.cylinder.color;
		else
			rgb = &shape->data.cone.color;
	}
	else if (type == LIGHT)
		rgb = &((t_light *)(s()->light->array[i]))->color;
	else if (type == VIEW)
		rgb = &(s()->ambient.color);
	else
		rgb = NULL;
	return (rgb);
}