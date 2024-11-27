#include "miniRT.h"

void	display(int x, int y, int color, char *text)
{
	mlx_string_put(s()->win.mlx, s()->win.disp, x, y, color, text);
}

void display_move_rotate(int x, int y)
{
    display(x, y,  0x87CEFA, "Movement and Rotation >"); //+2
    display(x += (25 * 6), y,  0xFFFFFF, "WASD : Move Up/Left/Dowm/Right"); //+5
    display(x += (35 * 6), y,  0xFFFFFF, "QE : Move Forward/Backward");
	if (s()->menu != LIGHT)
	{
    	display(x += (31 * 6), y,  0xFFFFFF, "IJKL : Rotate Up/Left/Dowm/Right");
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

void display_mode(int x, int y)
{
	display(x, y, 0x87CEFA, "Change Mode >");
	if (s()->menu == VIEW)
		display(x += (15 * 6), y, 0xFFFFFF, "C : Enter [Camera Edit Mode]");
	else
		display(x += (15 * 6), y, 0xFFFFFF, "V : Enter [View Mode]");
	if (s()->menu == VIEW)
	    display(x += (33 * 6), y, 0xFFFFFF, "B : Enter [LightSource Edit Mode]");
    else if (s()->menu == CAMERA)
		display(x += (26 * 6), y, 0xFFFFFF, "B : Enter [LightSource Edit Mode]");
	else
		display(x += (26 * 6), y, 0xFFFFFF, "C : Enter [Camera Edit Mode]");
	if (s()->menu == VIEW || s()->menu == CAMERA)
		display(x += (38 * 6), y, 0xFFFFFF, "M : Enter [Model Edit Mode]");
	else if (s()->menu == LIGHT)
	    display(x += (33 * 6), y, 0xFFFFFF, "M : Enter [Model Edit Mode]");
	else
    	display(x += (33 * 6), y, 0xFFFFFF, "B : Enter [LightSource Edit Mode]");
    display(x += (45 * 6), y, 0x87CEFA, "Render and Reset >");
    display(x += (20 * 6), y, 0xFFFFFF, "R : Render");
    display(x += (15* 6), y, 0xFFFFFF, "G : Reset to default");
}

void display_shape(int x, int y)
{
    t_shape *shape;

    shape = s()->shapes->array[s()->select];
    display(x, y,  0xFFD700, "Current Shape:");
    if (shape->type == SPHERE)
    {
        display(x += (16 * 6), y,  0xFFD700, "Sphere");
        display(x += (7 * 6), y,  0xFFD700, ft_itoa(shape->shape_id[SPHERE]));
    }
    else if (shape->type == PLANE)
    {
        display(x += (16 * 6), y,  0xFFD700, "Plane");
        display(x += (6 * 6), y,  0xFFD700, ft_itoa(shape->shape_id[PLANE]));
    }
    else if (shape->type == CYLINDER)
    {
        display(x += (16 * 6), y,  0xFFD700, "Cylinder");
        display(x += (9 * 6), y,  0xFFD700, ft_itoa(shape->shape_id[CYLINDER]));
    }
}

t_color	copy_color(t_color c)
{
	return ((t_color){
		.red = ft_within_range(c.red, 0, 255),
		.green = ft_within_range(c.green, 0, 255),
		.blue = ft_within_range(c.blue, 0, 255),
		.alpha = ft_within_range(0XFF, 0, 255)
	});
}

void display_color(int x, int y)
{
    t_shape *shape;
    t_color rgb;

    shape = s()->shapes->array[s()->select];
    display(x, y,  0x87CEFA, "Color:");
    if (shape->type == SPHERE)
        rgb = copy_color(shape->data.sphere.color);
    else if (shape->type == PLANE)
        rgb = copy_color(shape->data.plane.color);
    else if (shape->type == CYLINDER)
        rgb = copy_color(shape->data.cylinder.color);

    display(x += (9 * 6), y,  0xFFFFFF, ft_itoa(rgb.red));
    display(x += (ft_strlen(ft_itoa(rgb.red)) * 6), y,  0xFFFFFF, ", ");
    display(x += (2 * 6), y,  0xFFFFFF, ft_itoa(rgb.green));
    display(x += (ft_strlen(ft_itoa(rgb.green)) * 6), y,  0xFFFFFF, ", ");
    display(x += (2 * 6), y,  0xFFFFFF, ft_itoa(rgb.blue));
    
}
