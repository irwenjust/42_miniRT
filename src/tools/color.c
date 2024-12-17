/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:53:52 by likong            #+#    #+#             */
/*   Updated: 2024/11/18 15:42:19 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

t_color	parse_color(char **rgb)
{
	return ((t_color){
		.red = ft_within_range(ft_atoi(rgb[0]), 0, 255),
		.green = ft_within_range(ft_atoi(rgb[1]), 0, 255),
		.blue = ft_within_range(ft_atoi(rgb[2]), 0, 255),
		.alpha = ft_within_range(0XFF, 0, 255)
	});
}

t_color *get_color(int type, int i)
{
    t_shape *shape;
    t_color *rgb;

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


// t_color	copy_color(t_color c)
// {
// 	return ((t_color){
// 		.red = ft_within_range(c.red, 0, 255),
// 		.green = ft_within_range(c.green, 0, 255),
// 		.blue = ft_within_range(c.blue, 0, 255),
// 		.alpha = ft_within_range(0XFF, 0, 255)
// 	});
// }
