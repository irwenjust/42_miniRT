/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:29:01 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:29:04 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_light	*copy_light(t_light *light)
{
	t_light	*res;

	res = ft_calloc(1, sizeof(t_light));
	if (!res)
		return (NULL);
	*res = *light;
	return (res);
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

	coord = ft_split(arg[1], ',');
	if (!coord)
		return (ERROR("light: fail to split coordinate"), false);
	rgb = ft_split(arg[3], ',');
	if (!rgb)
	{
		free_matrix(coord);
		return (ERROR("light: fail to split color"), false);
	}
	light = new_light(coord, arg[2], rgb);
	free_matrix(coord);
	free_matrix(rgb);
	if (!light)
		return (ERROR("light: fail to create new light"), false);
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
