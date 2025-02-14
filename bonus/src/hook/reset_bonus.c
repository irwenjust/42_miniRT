/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:33:32 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:33:34 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	reset_camera(void)
{
	s()->camera = copy_camera(s()->ori_camera);
	init_viewport();
}

void	reset_lights(void)
{
	int	i;

	i = -1;
	while (++i < s()->light->size)
		s()->light->array[i] = copy_light(s()->ori_light->array[i]);
}

void	reset_shapes(void)
{
	int	i;

	i = -1;
	while (++i < s()->shapes->size)
		s()->shapes->array[i] = copy_shape(s()->ori_shapes->array[i]);
}

void	reset_all(void)
{
	s()->ambient = copy_ambient(s()->ori_ambient);
	reset_camera();
	reset_lights();
	reset_shapes();
}
