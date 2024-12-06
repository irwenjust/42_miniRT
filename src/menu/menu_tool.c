#include "miniRT.h"

void	display(int x, int y, int color, char *text)
{
	mlx_string_put(s()->win.mlx, s()->win.disp, x, y, color, text);
}

void display_move_rotate_size(int x, int y)
{
    display(x, y, 0x87CEFA, "Movement and Rotation >"); //+2
    display(x += (25 * 6), y, 0xFFFFFF, "WASD : Move Up/Left/Dowm/Right"); //+5
    display(x += (35 * 6), y, 0xFFFFFF, "QE : Move Forward/Backward");
	if (s()->menu != LIGHT)
	{
    	display(x += (31 * 6), y, 0xFFFFFF, "IJKL : Rotate Up/Left/Dowm/Right");
		display(x += (37 * 6), y, 0xFFFFFF, "UO : Rotate Forward/Backward");
	}
    if (s()->menu == SHAPE && ((t_shape *)(s()->shapes->array[s()->select]))->type != PLANE)
    {
        display(x += (38 * 6), y, 0x87CEFA, "Scaling >");
        display(x += (11 * 6), y, 0xFFFFFF, "Left/Right : -/+ Radius");
        if (((t_shape *)(s()->shapes->array[s()->select]))->type == CYLINDER)
        display(x += (28 * 6), y, 0xFFFFFF, "Down/Up : -/+ Height");
    }
}

void display_color(int x, int y, t_color *rgb)
{
    display(x, y, 0x87CEFA, "Color >");
    if (s()->select_rgb == 0)
        display(x += (9 * 6), y, 0xFFD700, ft_itoa(rgb->red));
    else
        display(x += (9 * 6), y, 0xFFFFFF, ft_itoa(rgb->red));
    display(x += (ft_strlen(ft_itoa(rgb->red)) * 6), y, 0xFFFFFF, ", ");
    if (s()->select_rgb == 1)
        display(x += (2 * 6), y, 0xFFD700, ft_itoa(rgb->green));
    else
        display(x += (2 * 6), y, 0xFFFFFF, ft_itoa(rgb->green));
    display(x += (ft_strlen(ft_itoa(rgb->green)) * 6), y, 0xFFFFFF, ", ");
    if (s()->select_rgb == 2)
        display(x += (2 * 6), y, 0xFFD700, ft_itoa(rgb->blue));
    else
        display(x += (2 * 6), y, 0xFFFFFF, ft_itoa(rgb->blue));
    display(x += (ft_strlen(ft_itoa(rgb->blue)) * 6), y, 0x87CEFA, "  >");
    display(x += (5 * 6), y, 0xFFFFFF, "P : Change Color Channel");
    display(x += (29 * 6), y, 0xFFFFFF, "[/] : +/- Color Value");
}

void display_brightness(int x, int y, double brightness)
{
    display(x, y, 0x87CEFA, "Brightness >");
    display(x += (14 * 6), y, 0xFFD700, ft_dtoa_simple(brightness));
    display(x += (5 * 6), y, 0x87CEFA, ">");
    display(x += (2 * 6), y, 0xFFFFFF, "Down/Up : -/+ Brightness");
}

void display_mode(int x, int y)
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
    if (s()->menu == VIEW || s()->menu == CAMERA)
        y -= 20;
    else
        x += (157 * 6);
    display(x, y, 0x87CEFA, "Render and Reset >");
    display(x += (20 * 6), y, 0xFFFFFF, "R : Render");
    display(x += (15* 6), y, 0xFFFFFF, "G : Reset to default");
}
