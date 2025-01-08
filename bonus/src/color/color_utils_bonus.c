/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:33:24 by likong            #+#    #+#             */
/*   Updated: 2025/01/08 11:59:04 by likong           ###   ########.fr       */
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
	return (color_create(c1.red - c2.red, c1.green - c2.green, c1.blue - c2.blue));
}

t_color	color_multi(t_color c1, t_color c2)
{
	return (color_create(c1.red * c2.red, c1.green * c2.green, c1.blue * c2.blue));
}
