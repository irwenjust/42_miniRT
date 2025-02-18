/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:40:33 by likong            #+#    #+#             */
/*   Updated: 2025/02/17 11:43:45 by likong           ###   ########.fr       */
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

static bool	check_light(char **arg)
{
	if (ft_matrix_size(arg) != 4 || !check_arg_format(arg, "2101"))
		return (error("light: wrong args format"), false);
	if (ft_atod(arg[2]) < 0.0 || ft_atod(arg[2]) > 1.0)
		return (error("light: wrong brightness ratio range"), false);
	if (!check_rgb(arg[3]))
		return (error("light: wrong color value"), false);
	return (true);
}

static t_light	*new_light(char **coord, char *brightness, char **rgb)
{
	t_light	*new;

	new = ft_calloc(1, sizeof(t_light));
	if (!new)
		return (NULL);
	*new = (t_light)
	{
		.point = parse_vector(coord),
		.brightness = ft_atod(brightness),
		.color = parse_color(rgb),
	};
	return (new);
}

bool	parse_light(int counter[3], char **arg, t_fclass *fclass)
{
	char	**coord;
	char	**rgb;
	t_light	*light;

	if (!check_light(arg))
		return (false);
	coord = ft_split(arg[1], ',');
	if (!coord)
		return (error("light: fail to split coordinate"), false);
	rgb = ft_split(arg[3], ',');
	if (!rgb)
	{
		free_matrix(coord);
		return (error("light: fail to split color"), false);
	}
	light = new_light(coord, arg[2], rgb);
	if (!light)
		return (error("light: fail to create new shape"), false);
	free_matrix(coord);
	free_matrix(rgb);
	if (!light)
		return (error("light: fail to create new light"), false);
	push_to_fclass(fclass, light);
	counter[2]++;
	return (true);
}

void	move_light(t_key *keys, t_light *light)
{
	if (keys->key[D])
		light->point.x += 0.3;
	else if (keys->key[A])
		light->point.x -= 0.3;
	else if (keys->key[W])
		light->point.y += 0.3;
	else if (keys->key[S])
		light->point.y -= 0.3;
	else if (keys->key[E])
		light->point.z += 0.3;
	else if (keys->key[Q])
		light->point.z -= 0.3;
}
