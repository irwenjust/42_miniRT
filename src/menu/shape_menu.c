#include "miniRT.h"

static void display_shape(int x, int y, t_shape *shape)
{
    display(x, y, 0xFFD700, "Current Shape:");
    if (shape->type == SPHERE)
    {
        display(x += (16 * 6), y, 0xFFD700, "Sphere");
        display(x += (7 * 6), y, 0xFFD700, ft_itoa(shape->shape_id[SPHERE]));
    }
    else if (shape->type == PLANE)
    {
        display(x += (16 * 6), y, 0xFFD700, "Plane");
        display(x += (6 * 6), y, 0xFFD700, ft_itoa(shape->shape_id[PLANE]));
    }
    else if (shape->type == CYLINDER)
    {
        display(x += (16 * 6), y, 0xFFD700, "Cylinder");
        display(x += (9 * 6), y, 0xFFD700, ft_itoa(shape->shape_id[CYLINDER]));
    }
    display(x += (4 * 6), y, 0x87CEFA, ">");
    display(x += (3 * 6), y, 0xFFFFFF, "TAB : To Next Shape");
}

static void display_shape_preset(int x, int y)
{
    display(x, y, 0x87CEFA, "Preset Shape Color >");
    display(x + (22 * 6), y, 0xFFFFFF, "1 : Red");
    display(x + (34 * 6), y, 0xFFFFFF, "2 : Yellow");
    display(x + (49 * 6), y, 0xFFFFFF, "3 : Green");
    display(x + (63 * 6), y, 0xFFFFFF, "4 : Blue");
    display(x + (76 * 6), y, 0xFFFFFF, "5 : Pink");
    display(x + (89 * 6), y, 0xFFFFFF, "6 : Purple");
    if (s()->preset == 1)
        display(x + (22 * 6), y, 0xFFD700, "1 : Red");
    if (s()->preset == 2)
        display(x + (34 * 6), y, 0xFFD700, "2 : Yellow");
    if (s()->preset == 3)
        display(x + (49 * 6), y, 0xFFD700, "3 : Green");
    if (s()->preset == 4)
        display(x + (63 * 6), y, 0xFFD700, "4 : Blue");
    if (s()->preset == 5)
        display(x + (76 * 6), y, 0xFFD700, "5 : Pink");
    if (s()->preset == 6)
        display(x + (89 * 6), y, 0xFFD700, "6 : Purple");
}

void shape_menu(int x, int y)
{
    t_shape *shape;

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