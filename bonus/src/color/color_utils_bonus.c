/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:33:24 by likong            #+#    #+#             */
/*   Updated: 2025/02/17 13:25:02 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_color	hex_to_color(unsigned int hex)
{
	t_color	color;

	color.red = (hex >> 24) & 0xFF;
	color.green = (hex >> 16) & 0xFF;
	color.blue = (hex >> 8) & 0xFF;
	color.alpha = hex & 0xFF;
	return (color);
}

void	put_pixel(t_color c, int x, int y)
{
	char	*dst;

	dst = s()->win.addr + (y * WIDTH + x) * (int)(s()->win.bpp * 0.125);
	*(unsigned int *)dst = (c.alpha << 24 | c.red << 16
			| c.green << 8 | c.blue);
}

t_color	copy_color(t_color c)
{
	return ((t_color){
		.red = ft_within_range(c.red, 0, 255),
		.green = ft_within_range(c.green, 0, 255),
		.blue = ft_within_range(c.blue, 0, 255),
		.alpha = ft_within_range(0XFF, 0, 255)
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

void	put_test_pixel(t_image *img, int i, int j, t_color color)
{
	int	pixel;

	pixel = i * img->size_line + j * (img->bpp / 8);
	img->data[pixel + 0] = (unsigned char)(color.red);
	img->data[pixel + 1] = (unsigned char)(color.green);
	img->data[pixel + 2] = (unsigned char)(color.blue);
	img->data[pixel + 3] = (unsigned char)(color.alpha);
}
