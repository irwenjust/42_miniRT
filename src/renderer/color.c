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

t_color	parse_color(char **rgb)
{
	return ((t_color){
		.red = ft_within_range(ft_atoi(rgb[0]), 0, 255),
		.green = ft_within_range(ft_atoi(rgb[1]), 0, 255),
		.blue = ft_within_range(ft_atoi(rgb[2]), 0, 255),
		.alpha = ft_within_range(0XFF, 0, 255)
	});
}
