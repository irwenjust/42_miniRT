/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:17:45 by likong            #+#    #+#             */
/*   Updated: 2024/12/31 12:29:32 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_color	copy_ambient_color(t_color c)
{
	return ((t_color){
		.red = ft_within_range(c.red, 0, 255),
		.green = ft_within_range(c.green, 0, 255),
		.blue = ft_within_range(c.blue, 0, 255),
		.alpha = ft_within_range(0XFF, 0, 255)
	});
}

t_ambient	copy_ambient(t_ambient ambient)
{
	t_ambient	dst;

	dst.brightness = ambient.brightness;
	dst.color = copy_ambient_color(ambient.color);
	return (dst);
}

//add ambient color and brightness to colosest color
t_color	check_ambient(t_color color)
{
	t_color	ambient;

	ambient = add_bright_to_color(s()->ambient.color, s()->ambient.brightness);
	return (mix_color(color, ambient));
}

bool	parse_ambient(int counter[3], char **arg, t_ambient *ambient)
{
	char	**rgb;

	if (ft_matrix_size(arg) != 3 || !check_arg_format(arg, "201"))
		return (ERROR("ambient: wrong args format"), false);
	ambient->brightness = ft_atod(arg[1]);
	if (ambient->brightness < 0.0 || ambient->brightness > 1.0)
		return (ERROR("ambient: wrong brightness ratio range"), false);
	if (!check_rgb(arg[2]))
		return (ERROR("ambient: wrong color value"), false);
	rgb = ft_split(arg[2], ',');
	if (!rgb)
		return (ERROR("ambient: fail to split color"), false);
	ambient->color = parse_color(rgb);
	free_matrix(rgb);
	counter[0]++;
	return (true);
}
