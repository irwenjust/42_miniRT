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

//bool parse_light(int counter[3], char **arg, t_fclass *fclass)
//{
//	char **coord;
//	char **rgb;
//	t_light *light;

//	if (ft_matrix_size(arg) != 4)
//		return (ERROR("light: needs 4 arguments"), false);
//	//check syntax
//	//coord
//	coord = ft_split(arg[1], ',');
//	//check coord
//	//britghtness
//	if (ft_atod(arg[2]) < 0.0 || ft_atod(arg[2]) > 1.0)
//		return (ERROR("light: error happend in lighting ratio range"), false);
//	//rgb
//	rgb = ft_split(arg[3], ',');
//	if (!rgb)
//		return (ERROR("ambient: error in split color"), false);
	
//	light = light_new();
//	push_to_fclass(fclass, light);
//	free_matrix(coord);
//	free_matrix(rgb);
//	counter[2]++;
//	return (true);
//}
