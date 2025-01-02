

#include "miniRT_bonus.h"

void	display_move_rotate_size(int x, int y)
{
	display(x, y, 0x87CEFA, "Movement >");
	display(x += (12 * 6), y, 0xFFFFFF, "D/A : Move +/- along X-axis");
	display(x += (32 * 6), y, 0xFFFFFF, "W/S : Move +/- along Y-axis");
	display(x += (32 * 6), y, 0xFFFFFF, "E/Q : Move +/- along Z-axis");
	if (s()->menu != LIGHT)
	{
		display(x += (32 * 6), y, 0x87CEFA, "Rotation >");
		display(x += (12 * 6), y, 0xFFFFFF, "L/J : Rotate +/- around X-axis");
		display(x += (32 * 6), y, 0xFFFFFF, "I/K : Rotate +/- around Y-axis");
		display(x += (32 * 6), y, 0xFFFFFF, "O/U : Rotate +/- around Z-axis");
	}
	if (s()->menu == SHAPE
		&& ((t_shape *)(s()->shapes->array[s()->select]))->type != PLANE)
	{
		display(x += (36 * 6), y, 0x87CEFA, "Scaling >");
		display(x += (11 * 6), y, 0xFFFFFF, "Left/Right : -/+ Radius");
		if (((t_shape *)(s()->shapes->array[s()->select]))->type == CYLINDER)
			display(x, y += 20, 0xFFFFFF, "Down/Up : -/+ Height");
	}
}

void	display_color(int x, int y, t_color *rgb)
{
	display(x, y, 0x87CEFA, "Color >");
	if (s()->select_rgb == 0)
		display_clear(x += (9 * 6), y, 0xFFD700, ft_itoa(rgb->red));
	else
		display_clear(x += (9 * 6), y, 0xFFFFFF, ft_itoa(rgb->red));
	display(x += (ft_intlen(rgb->red) * 6), y, 0xFFFFFF, ", ");
	if (s()->select_rgb == 1)
		display_clear(x += (2 * 6), y, 0xFFD700, ft_itoa(rgb->green));
	else
		display_clear(x += (2 * 6), y, 0xFFFFFF, ft_itoa(rgb->green));
	display(x += (ft_intlen(rgb->green) * 6), y, 0xFFFFFF, ", ");
	if (s()->select_rgb == 2)
		display_clear(x += (2 * 6), y, 0xFFD700, ft_itoa(rgb->blue));
	else
		display_clear(x += (2 * 6), y, 0xFFFFFF, ft_itoa(rgb->blue));
	display(x += (ft_intlen(rgb->blue) * 6), y, 0x87CEFA, "  >");
	display(x += (5 * 6), y, 0xFFFFFF, "P : Change Color Channel");
	display(x += (29 * 6), y, 0xFFFFFF, "[/] : +/- Color Value");
}

void	display_brightness(int x, int y, double brightness)
{
	display(x, y, 0x87CEFA, "Brightness >");
	display_clear(x += (14 * 6), y, 0xFFD700, ft_dtoa_one(brightness));
	display(x += (5 * 6), y, 0x87CEFA, ">");
	display(x += (2 * 6), y, 0xFFFFFF, "Up/Down : +/- Brightness");
}

void	display_mode(int x, int y)
{
	display(x, y, 0x87CEFA, "Change Mode >");
	display(x + (15 * 6), y, 0xFFFFFF, "V : Enter [View Mode]");
	display(x + (41 * 6), y, 0xFFFFFF, "C : Enter [Camera Edit Mode]");
	display(x + (74 * 6), y, 0xFFFFFF, "B : Enter [LightSource Edit Mode]");
	display(x + (112 * 6), y, 0xFFFFFF, "M : Enter [Model Edit Mode]");
	if (s()->menu == VIEW)
		display(x + (15 * 6), y, 0xFFD700, "V : Enter [View Mode]");
	else if (s()->menu == CAMERA)
		display(x + (41 * 6), y, 0xFFD700, "C : Enter [Camera Edit Mode]");
	else if (s()->menu == LIGHT)
		display(x + (74 * 6), y, 0xFFD700, "B : Enter [LightSource Edit Mode]");
	else
		display(x + (112 * 6), y, 0xFFD700, "M : Enter [Model Edit Mode]");
	if (s()->menu == VIEW)
		y -= 20;
	else
		x += (157 * 6);
	display(x, y, 0x87CEFA, "Render and Reset >");
	display(x += (20 * 6), y, 0xFFFFFF, "R : Render");
	display(x += (15 * 6), y, 0xFFFFFF, "G : Reset to default");
}
