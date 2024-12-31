/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:58:15 by yzhan             #+#    #+#             */
/*   Updated: 2024/12/31 13:58:52 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
