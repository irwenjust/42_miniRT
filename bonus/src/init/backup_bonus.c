/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:09:37 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:09:40 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	backup_scene(void)
{
	int		i;
	t_light	*light;
	t_shape	*shape;

	s()->ori_ambient = copy_ambient(s()->ambient);
	s()->ori_camera = copy_camera(s()->camera);
	i = -1;
	while (++i < s()->light->size)
	{
		light = copy_light(s()->light->array[i]);
		push_to_fclass(s()->ori_light, light);
	}
	i = -1;
	while (++i < s()->shapes->size)
	{
		shape = copy_shape(s()->shapes->array[i]);
		push_to_fclass(s()->ori_shapes, shape);
	}
}
