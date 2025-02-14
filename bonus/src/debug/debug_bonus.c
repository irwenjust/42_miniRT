/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:08:18 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:08:23 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	print_light(t_light *light)
{
	printf("Light coordinate: %1lf,%1lf,%1lf\n",
		light->point.x, light->point.y, light->point.z);
	printf("Light brightness level: %1lf\n", light->brightness);
	printf("Light color: %d,%d,%d\n",
		light->color.red, light->color.green, light->color.blue);
}

void	print_camera(t_camera *camera)
{
	printf("camera coordinate: %f,%f,%f\n",
		camera->coordinate.x, camera->coordinate.y, camera->coordinate.z);
	printf("camera normal: %.2lf,%.2lf,%.2lf\n",
		camera->normal.x, camera->normal.y, camera->normal.z);
	printf("camera fov: %d\n", camera->fov);
}

void	print_box(t_aabb box)
{
	printf("AABB min: (%f, %f, %f), max: (%f, %f, %f)\n",
		box.min.x, box.min.y, box.min.z,
		box.max.x, box.max.y, box.max.z);
}
