/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:08:48 by yzhan             #+#    #+#             */
/*   Updated: 2024/12/31 14:10:12 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	display_light_preset(int x, int y)
{
	display(x, y, 0x87CEFA, "Preset Light Color & Brightness >");
	display(x + (35 * 6), y, 0xFFFFFF, "1 : Warm White");
	display(x + (54 * 6), y, 0xFFFFFF, "2 : Cold White");
	display(x + (73 * 6), y, 0xFFFFFF, "3 : Sunset");
	display(x + (88 * 6), y, 0xFFFFFF, "4 : Moonlight");
	display(x + (106 * 6), y, 0xFFFFFF, "5 : Cyberpunk");
	display(x + (124 * 6), y, 0xFFFFFF, "6 : Toxic");
	if (s()->preset == 1)
		display(x + (35 * 6), y, 0xFFD700, "1 : Warm White");
	if (s()->preset == 2)
		display(x + (54 * 6), y, 0xFFD700, "2 : Cold White");
	if (s()->preset == 3)
		display(x + (73 * 6), y, 0xFFD700, "3 : Sunset");
	if (s()->preset == 4)
		display(x + (88 * 6), y, 0xFFD700, "4 : Moonlight");
	if (s()->preset == 5)
		display(x + (106 * 6), y, 0xFFD700, "5 : Cyberpunk");
	if (s()->preset == 6)
		display(x + (124 * 6), y, 0xFFD700, "6 : Toxic");
}

void	light_menu(int x, int y)
{
	t_light	*light;

	light = s()->light->array[s()->select];
	display(x, y, 0xFFFFFF, "- LightSource Edit Mode -");
	display_move_rotate_size(x, y + 20);
	display_color(x, y + 40, &light->color);
	display_brightness(x + (96 * 6), y + 40, light->brightness);
	display_light_preset(x, y + 60);
	display_mode(x, y + 80);
}
