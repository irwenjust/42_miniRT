/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:27:21 by yzhan             #+#    #+#             */
/*   Updated: 2024/12/31 14:30:32 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	display_shape(int x, int y, t_shape *shape)
{
	display(x, y, 0xFFD700, "Current Shape:");
	if (shape->type == SPHERE)
	{
		display(x += (16 * 6), y, 0xFFD700, "Sphere");
		display_clear(x += (7 * 6), y, 0xFFD700,
			ft_itoa(shape->shape_id[SPHERE]));
	}
	else if (shape->type == PLANE)
	{
		display(x += (16 * 6), y, 0xFFD700, "Plane");
		display_clear(x += (6 * 6), y, 0xFFD700,
			ft_itoa(shape->shape_id[PLANE]));
	}
	else if (shape->type == CYLINDER)
	{
		display(x += (16 * 6), y, 0xFFD700, "Cylinder");
		display_clear(x += (9 * 6), y, 0xFFD700,
			ft_itoa(shape->shape_id[CYLINDER]));
	}
	display(x += (4 * 6), y, 0x87CEFA, ">");
	display(x += (3 * 6), y, 0xFFFFFF, "TAB : To Next Shape");
}

static void	display_shape_preset(int x, int y)
{
	display(x, y, 0x87CEFA, "Preset Shape ColorSet >");
	display(x + (25 * 6), y, 0xFFFFFF, "1 : Soft Dream");
	display(x + (41 * 6), y, 0xFFFFFF, "2 : Sunset");
	display(x + (56 * 6), y, 0xFFFFFF, "3 : Fire");
	display(x + (69 * 6), y, 0xFFFFFF, "4 : Blue Style");
	display(x + (88 * 6), y, 0xFFFFFF, "5 : Forest");
	display(x + (103 * 6), y, 0xFFFFFF, "6 : Coffee");
	if (s()->preset == 1)
		display(x + (22 * 6), y, 0xFFD700, "1 : Soft Dream");
	if (s()->preset == 2)
		display(x + (41 * 6), y, 0xFFD700, "2 : Sunset");
	if (s()->preset == 3)
		display(x + (56 * 6), y, 0xFFD700, "3 : Fire");
	if (s()->preset == 4)
		display(x + (69 * 6), y, 0xFFD700, "4 : Blue Style");
	if (s()->preset == 5)
		display(x + (88 * 6), y, 0xFFD700, "5 : Forest");
	if (s()->preset == 6)
		display(x + (103 * 6), y, 0xFFD700, "6 : Coffee");
}

void	shape_menu(int x, int y)
{
	t_shape	*shape;

	shape = s()->shapes->array[s()->select];
	display(x, y, 0xFFFFFF, "- Model Edit Mode -");
	display_shape(x + (24 * 6), y, shape);
	display_move_rotate_size(x, y + 20);
	if (shape->type == SPHERE)
		display_color(x, y + 40, &shape->data.sphere.color);
	else if (shape->type == PLANE)
		display_color(x, y + 40, &shape->data.plane.color);
	else
		display_color(x, y + 40, &shape->data.cylinder.color);
	display_shape_preset(x, y + 60);
	display_mode(x, y + 80);
}
