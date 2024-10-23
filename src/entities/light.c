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

void	print_light(t_light *light)
{
	printf("Light coordinate: %1lf,%1lf,%1lf\n",
		light->coordinate.x, light->coordinate.y, light->coordinate.z);
	printf("Light brightness level: %1lf\n", light->brightness);
	printf("Light color: %d,%d,%d\n",
		light->color.red, light->color.green, light->color.blue);
}

t_light	*copy_light(t_light *light)
{
	t_light	*res;

	res = ft_calloc(1, sizeof(t_light));
	if (!res)
		return (NULL);
	*res = *light;
	return (res);
}
