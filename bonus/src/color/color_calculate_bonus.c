/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:14:00 by likong            #+#    #+#             */
/*   Updated: 2025/01/07 17:14:03 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_color	add_color(t_color c1, t_color c2)
{
	return ((t_color){
		.red = ft_within_range(c1.red + c2.red, 0, 255),
		.green = ft_within_range(c1.green + c2.green, 0, 255),
		.blue = ft_within_range(c1.blue + c2.blue, 0, 255),
		.alpha = ft_within_range(0XFF, 0, 255)
	});
}

t_color	sub_color(t_color c1, t_color c2)
{
	return ((t_color){
		.red = ft_within_range(c1.red - c2.red, 0, 255),
		.green = ft_within_range(c1.green - c2.green, 0, 255),
		.blue = ft_within_range(c1.blue - c2.blue, 0, 255),
		.alpha = ft_within_range(0XFF, 0, 255)
	});
}

t_color	multi_color(t_color color, double factor)
{
	return ((t_color){
		.red = ft_within_range(color.red * factor, 0, 255),
		.green = ft_within_range(color.green * factor, 0, 255),
		.blue = ft_within_range(color.blue * factor, 0, 255),
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




