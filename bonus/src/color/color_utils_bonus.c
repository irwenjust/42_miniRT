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

t_color	color_sub(t_color c1, t_color c2)
{
	return ((t_color){
		.red = ft_within_range(c1.red - c2.red, 0, 255),
		.green = ft_within_range(c1.green - c2.green, 0, 255),
		.blue = ft_within_range(c1.blue - c2.blue, 0, 255),
		.alpha = ft_within_range(0XFF, 0, 255)
	});
}

