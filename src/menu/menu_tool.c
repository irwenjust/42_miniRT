#include "miniRT.h"

void	display(int x, int y, int color, char *text, int f)
{
    if (f == 1 && !text)
        error_exit("Fail in menu display");
    mlx_string_put(s()->win.mlx, s()->win.disp, x, y, color, text);
    if (f == 1)
        free(text);
}

void display_move_rotate_size(int x, int y)
{
    display(x, y, 0x87CEFA, "Movement >", 0);
    display(x += (12 * 6), y, 0xFFFFFF, "D/A : Move +/- along X-axis", 0);
    display(x += (32 * 6), y, 0xFFFFFF, "W/S : Move +/- along Y-axis", 0);
    display(x += (32 * 6), y, 0xFFFFFF, "E/Q : Move +/- along Z-axis", 0);
	if (s()->menu != LIGHT)
	{
        display(x += (32 * 6), y, 0x87CEFA, "Rotation >", 0);
        display(x += (12 * 6), y, 0xFFFFFF, "I/K : Rotate +/- around X-axis", 0);
    	display(x += (32 * 6), y, 0xFFFFFF, "L/J : Rotate +/- around Y-axis", 0);
    	display(x += (32 * 6), y, 0xFFFFFF, "O/U : Rotate +/- around Z-axis", 0);
	}
    if (s()->menu == SHAPE && ((t_shape *)(s()->shapes->array[s()->select]))->type != PLANE)
    {
        display(x += (36 * 6), y, 0x87CEFA, "Scaling >", 0);
        display(x += (11 * 6), y, 0xFFFFFF, "Left/Right : -/+ Radius", 0);
        if (((t_shape *)(s()->shapes->array[s()->select]))->type == CYLINDER)
            display(x, y += 20, 0xFFFFFF, "Down/Up : -/+ Height", 0);
    }
}

void display_color(int x, int y, t_color *rgb)
{
    display(x, y, 0x87CEFA, "Color >", 0);
    if (s()->select_rgb == 0)
        display(x += (9 * 6), y, 0xFFD700, ft_itoa(rgb->red), 1);
    else
        display(x += (9 * 6), y, 0xFFFFFF, ft_itoa(rgb->red), 1);
    display(x += (ft_intlen(rgb->red) * 6), y, 0xFFFFFF, ", ", 0);
    if (s()->select_rgb == 1)
        display(x += (2 * 6), y, 0xFFD700, ft_itoa(rgb->green), 1);
    else
        display(x += (2 * 6), y, 0xFFFFFF, ft_itoa(rgb->green), 1);
    display(x += (ft_intlen(rgb->green) * 6), y, 0xFFFFFF, ", ", 0);
    if (s()->select_rgb == 2)
        display(x += (2 * 6), y, 0xFFD700, ft_itoa(rgb->blue), 1);
    else
        display(x += (2 * 6), y, 0xFFFFFF, ft_itoa(rgb->blue), 1);
    display(x += (ft_intlen(rgb->blue) * 6), y, 0x87CEFA, "  >", 0);
    display(x += (5 * 6), y, 0xFFFFFF, "P : Change Color Channel", 0);
    display(x += (29 * 6), y, 0xFFFFFF, "[/] : +/- Color Value", 0);
}

void display_brightness(int x, int y, double brightness)
{
    display(x, y, 0x87CEFA, "Brightness >", 0);
    display(x += (14 * 6), y, 0xFFD700, ft_dtoa_simple(brightness), 1);
    display(x += (5 * 6), y, 0x87CEFA, ">", 0);
    display(x += (2 * 6), y, 0xFFFFFF, "Down/Up : -/+ Brightness", 0);
}

void display_mode(int x, int y)
{
	display(x, y, 0x87CEFA, "Change Mode >", 0);
    display(x + (15 * 6), y, 0xFFFFFF, "V : Enter [View Mode]", 0);
    display(x + (41 * 6), y, 0xFFFFFF, "C : Enter [Camera Edit Mode]", 0);
    display(x + (74 * 6), y, 0xFFFFFF, "B : Enter [LightSource Edit Mode]", 0);
    display(x + (112 * 6), y, 0xFFFFFF, "M : Enter [Model Edit Mode]", 0);
	if (s()->menu == VIEW)
		display(x + (15 * 6), y, 0xFFD700, "V : Enter [View Mode]", 0);
    else if (s()->menu == CAMERA)
		display(x + (41 * 6), y, 0xFFD700, "C : Enter [Camera Edit Mode]", 0);
	else if (s()->menu == LIGHT)
	    display(x + (74 * 6), y, 0xFFD700, "B : Enter [LightSource Edit Mode]", 0);
	else
    	display(x + (112 * 6), y, 0xFFD700, "M : Enter [Model Edit Mode]", 0);
    if (s()->menu == VIEW || s()->menu == CAMERA)
        y -= 20;
    else
        x += (157 * 6);
    display(x, y, 0x87CEFA, "Render and Reset >", 0);
    display(x += (20 * 6), y, 0xFFFFFF, "R : Render", 0);
    display(x += (15* 6), y, 0xFFFFFF, "G : Reset to default", 0);
}
