/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:40:33 by likong            #+#    #+#             */
/*   Updated: 2024/10/22 16:55:40 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_light	*copy_light(t_light *light)
{
	t_light	*res;

	res = ft_calloc(1, sizeof(t_light));
	if (!res)
		return (NULL);
	*res = *light;
	return (res);
}

t_light *light_new(char **coord, char *brightness, char **rgb)
{
	t_light *new;

	new = ft_calloc(1, sizeof(t_light));
	if (!new)
		return (NULL);
	*new = (t_light)
	{
		.coordinate = parse_vector(coord),
		.brightness = ft_atod(brightness),
		.color = parse_color(rgb),
	};
	return (new);
}

bool parse_light(int counter[3], char **arg, t_fclass *fclass)
{
	char **coord;
	char **rgb;
	t_light *light;

	if (ft_matrix_size(arg) != 4)
		return (ERROR("light: needs 4 arguments"), false);
	//check syntax
	//if (!check_syntax(arg, "0101"))
	//	return (ERROR("light: Misconfiguration in commas/numbers"), false);
	//check britghtness
	if (ft_atod(arg[2]) < 0.0 || ft_atod(arg[2]) > 1.0)
		return (ERROR("light: error happend in lighting ratio range"), false);
	//check color
	if (!check_rgb(arg[3]))
		return (ERROR("light: error in color"), false);
	//get data
	coord = ft_split(arg[1], ',');
	rgb = ft_split(arg[3], ',');
	if (!coord || !rgb)
		return (ERROR("light: error in split coord or color"), false);
	//push to light
	light = light_new(coord, arg[2], rgb); //TODO
	if (!light)
		return (ERROR("light: error in create new light"), false);
	push_to_fclass(fclass, light);
	free_matrix(coord);
	free_matrix(rgb);
	counter[2]++;
	return (true);
}
