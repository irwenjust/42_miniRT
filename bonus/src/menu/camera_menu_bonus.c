/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_menu_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:37:41 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:37:43 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static void	display_camera_preset(int x, int y)
{
	display(x, y, 0x87CEFA, "Preset Camera >");
	display(x + (17 * 6), y, 0xFFFFFF, "1 : Front View");
	display(x + (36 * 6), y, 0xFFFFFF, "2 : Back View");
	display(x + (54 * 6), y, 0xFFFFFF, "3 : Top View");
	display(x + (71 * 6), y, 0xFFFFFF, "4 : Bottom View");
	display(x + (91 * 6), y, 0xFFFFFF, "5 : Left View");
	display(x + (109 * 6), y, 0xFFFFFF, "6 : Right View");
	if (s()->preset == 1)
		display(x + (17 * 6), y, 0xFFD700, "1 : Front View");
	if (s()->preset == 2)
		display(x + (36 * 6), y, 0xFFD700, "2 : Back View");
	if (s()->preset == 3)
		display(x + (54 * 6), y, 0xFFD700, "3 : Top View");
	if (s()->preset == 4)
		display(x + (71 * 6), y, 0xFFD700, "4 : Bottom View");
	if (s()->preset == 5)
		display(x + (91 * 6), y, 0xFFD700, "5 : Left View");
	if (s()->preset == 6)
		display(x + (109 * 6), y, 0xFFD700, "6 : Right View");
}

void	camera_menu(int x, int y)
{
	display(x, y, 0xFFFFFF, "- Camera Edit Mode -");
	display_move_rotate_size(x, y + 20);
	display(x, y + 40, 0x87CEFA, "Camera FOV >");
	display_f(x + (15 * 6), y + 40, 0xFFD700, ft_itoa(s()->camera.fov));
	display(x + (20 * 6), y + 40, 0x87CEFA, ">");
	display(x + (22 * 6), y + 40, 0xFFFFFF, "Up/Down : +/- FOV");
	display_camera_preset(x, y + 60);
	display_mode(x, y + 80);
}
