/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_shape_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:08:28 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:08:32 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static void	print_sphere(t_sphere sphere)
{
	printf("Sphere:\n");
	printf("  Center: %.2lf, %.2lf, %.2lf\n", \
		sphere.center.x, sphere.center.y, sphere.center.z);
	printf("  Radius: %.2lf\n", sphere.radius);
	printf("  Color:  %d, %d, %d\n", sphere.color.red,
		sphere.color.green, sphere.color.blue);
}

static void	print_plane(t_plane plane)
{
	printf("plane:\n");
	printf("  Center: %.2lf, %.2lf, %.2lf\n", \
		plane.center.x, plane.center.y, plane.center.z);
	printf("  Normal: %.2lf, %.2lf, %.2lf\n", \
		plane.normal.x, plane.normal.y, plane.normal.z);
	printf("  Color:  %d, %d, %d\n", plane.color.red,
		plane.color.green, plane.color.blue);
}

static void	print_cylinder(t_cylinder cylinder)
{
	printf("cylinder:\n");
	printf("  Center: %.2lf, %.2lf, %.2lf\n", \
		cylinder.center.x, cylinder.center.y, cylinder.center.z);
	printf("  Normal: %.2lf, %.2lf, %.2lf\n", \
		cylinder.normal.x, cylinder.normal.y, cylinder.normal.z);
	printf("  Color:  %d, %d, %d\n", cylinder.color.red,
		cylinder.color.green, cylinder.color.blue);
}

static void	print_cone(t_cone cone)
{
	printf("cone:\n");
	printf("  tip: %.2lf, %.2lf, %.2lf\n", \
		cone.tip.x, cone.tip.y, cone.tip.z);
	printf("  Base: %.2lf, %.2lf, %.2lf\n", \
		cone.base.x, cone.base.y, cone.base.z);
	printf("  Center: %.2lf, %.2lf, %.2lf\n", \
		cone.center.x, cone.center.y, cone.center.z);
	printf("  Normal: %.2lf, %.2lf, %.2lf\n", \
		cone.normal.x, cone.normal.y, cone.normal.z);
	printf("  Color:  %d, %d, %d\n", cone.color.red,
		cone.color.green, cone.color.blue);
	printf("  radius:  %f, height %f, angle %f\n", cone.radius,
		cone.height, cone.angle);
}

void	print_shape(t_shape *shape)
{
	printf("ID: %d\n", shape->id);
	if (shape->type == SPHERE)
		print_sphere(shape->data.sphere);
	if (shape->type == PLANE)
		print_plane(shape->data.plane);
	if (shape->type == CYLINDER)
		print_cylinder(shape->data.cylinder);
	if (shape->type == CONE)
		print_cone(shape->data.cone);
}
