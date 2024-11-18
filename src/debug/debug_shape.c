/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:11:39 by likong            #+#    #+#             */
/*   Updated: 2024/11/18 15:47:17 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//static void	print_sphere(t_sphere sphere)
//{
//	printf("Sphere:\n");
//	printf("  Center: %.2lf, %.2lf, %.2lf\n", \
//		sphere.center.x, sphere.center.y, sphere.center.z);
//	printf("  Radius: %.2lf\n", sphere.radius);
//	printf("  Color:  %d, %d, %d\n", sphere.color.red,
//		sphere.color.green, sphere.color.blue);
//}

static void print_plane(t_plane plane)
{
	printf("plane:\n");
	printf("  Center: %.2lf, %.2lf, %.2lf\n", \
		plane.center.x, plane.center.y, plane.center.z);
	printf("  Center: %.2lf, %.2lf, %.2lf\n", \
		plane.normal.x, plane.normal.y, plane.normal.z);
	printf("  Color:  %d, %d, %d\n", plane.color.red,
		plane.color.green, plane.color.blue);
}

void	print_shape(t_shape *shape)
{
	printf("ID: %d\n", shape->id);
	//if (shape->type == SPHERE)
	//	print_sphere(shape->data.sphere);
	if (shape->type == PLANE)
		print_plane(shape->data.plane);
}

void	print_light(t_light *light)
{
	printf("Light coordinate: %1lf,%1lf,%1lf\n",
		light->point.x, light->point.y, light->point.z);
	printf("Light brightness level: %1lf\n", light->brightness);
	printf("Light color: %d,%d,%d\n",
		light->color.red, light->color.green, light->color.blue);
}