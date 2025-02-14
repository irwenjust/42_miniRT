/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:37:52 by yzhan             #+#    #+#             */
/*   Updated: 2024/12/31 13:42:46 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	light_preset(int preset)
{
	t_light	*light;

	light = s()->light->array[s()->select];
	if (preset == 1)
		light->color = hex_to_color(WARM_W);
	else if (preset == 2)
		light->color = hex_to_color(COLD_W);
	else if (preset == 3)
		light->color = hex_to_color(SUNSET);
	else if (preset == 4)
		light->color = hex_to_color(MOON);
	else if (preset == 5)
		light->color = hex_to_color(CYERPK);
	else if (preset == 6)
		light->color = hex_to_color(TOXIC);
	if (preset == 1 || preset == 2 || preset == 5)
		light->brightness = 1.0;
	else if (preset == 3 || preset == 6)
		light->brightness = 0.7;
	else if (preset == 4)
		light->brightness = 0.4;
}

static void	shape_preset(int preset)
{
	int				i;
	int				j;
	t_color			*color;
	unsigned int	*color_palette;

	if (preset == 1)
		color_palette = (unsigned int []){CS1_C1, CS1_C2, CS1_C3, CS1_C4};
	else if (preset == 2)
		color_palette = (unsigned int []){CS2_C1, CS2_C2, CS2_C3, CS2_C4};
	else if (preset == 3)
		color_palette = (unsigned int []){CS3_C1, CS3_C2, CS3_C3, CS3_C4};
	else if (preset == 4)
		color_palette = (unsigned int []){CS4_C1, CS4_C2, CS4_C3, CS4_C4};
	else if (preset == 5)
		color_palette = (unsigned int []){CS5_C1, CS5_C2, CS5_C3, CS5_C4};
	else
		color_palette = (unsigned int []){CS6_C1, CS6_C2, CS6_C3, CS6_C4};
	i = -1;
	j = 0;
	while (++i < s()->shapes->size)
	{
		color = get_color(SHAPE, i);
		*color = hex_to_color(color_palette[j]);
		j = (j + 1) % 4;
	}
}

static void	view_preset(int preset)
{
	camera_preset(preset);
	light_preset(preset);
	shape_preset(preset);
}

void	switch_preset(int preset)
{
	if (s()->menu == CAMERA)
		camera_preset(preset);
	else if (s()->menu == LIGHT)
		light_preset(preset);
	else if (s()->menu == SHAPE)
		shape_preset(preset);
	else if (s()->menu == VIEW)
		view_preset(preset);
}
