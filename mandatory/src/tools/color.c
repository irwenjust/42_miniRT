/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:53:52 by likong            #+#    #+#             */
/*   Updated: 2024/12/31 14:47:05 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	hex_to_color(unsigned int hex)
{
	t_color	color;

	color.red = (hex >> 24) & 0xFF;
	color.green = (hex >> 16) & 0xFF;
	color.blue = (hex >> 8) & 0xFF;
	color.alpha = hex & 0xFF;
	return (color);
}

t_color	add_bright_to_color(t_color color, double brightness)
{
	return ((t_color){
		.red = ft_within_range(color.red * brightness, 0, 255),
		.green = ft_within_range(color.green * brightness, 0, 255),
		.blue = ft_within_range(color.blue * brightness, 0, 255),
		.alpha = ft_within_range(0XFF, 0, 255)
	});
}

t_color	add_color(t_color c1, t_color c2)
{
	return ((t_color){
		.red = ft_within_range(c1.red + c2.red, 0, 255),
		.green = ft_within_range(c1.green + c2.green, 0, 255),
		.blue = ft_within_range(c1.blue + c2.blue, 0, 255),
		.alpha = ft_within_range(0XFF, 0, 255)
	});
}

t_color	mix_color(t_color c1, t_color c2)
{
	return ((t_color){
		.red = ft_within_range(c1.red * c2.red / 255.0, 0, 255),
		.green = ft_within_range(c1.green * c2.green / 255.0, 0, 255),
		.blue = ft_within_range(c1.blue * c2.blue / 255.0, 0, 255),
		.alpha = c1.alpha
	});
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
		else
			rgb = &shape->data.cylinder.color;
	}
	else if (type == LIGHT)
		rgb = &((t_light *)(s()->light->array[0]))->color;
	else if (type == VIEW)
		rgb = &(s()->ambient.color);
	else
		rgb = NULL;
	return (rgb);
}
