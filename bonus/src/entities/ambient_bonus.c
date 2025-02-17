/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:28:44 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/17 11:11:24 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_ambient	copy_ambient(t_ambient ambient)
{
	t_ambient	dst;

	dst.brightness = ambient.brightness;
	dst.color = copy_color(ambient.color);
	return (dst);
}

//add ambient color and brightness to colosest color
t_color	check_ambient(t_color color)
{
	t_color	ambient;

	ambient = multi_color(s()->ambient.color, s()->ambient.brightness);
	return (mix_color(color, ambient));
}

bool	parse_ambient(int counter[3], char **arg, t_ambient *ambient)
{
	char	**rgb;

	ambient->brightness = ft_atod(arg[1]);
	rgb = ft_split(arg[2], ',');
	if (!rgb)
		return (error("ambient: fail to split color"), false);
	ambient->color = parse_color(rgb);
	free_matrix(rgb);
	counter[0]++;
	return (true);
}
