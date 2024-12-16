#include "miniRT.h"

static void display_shape(int x, int y, t_shape *shape)
{
    display(x, y, 0xFFD700, "Current Shape:", 0);
    if (shape->type == SPHERE)
    {
        display(x += (16 * 6), y, 0xFFD700, "Sphere", 0);
        display(x += (7 * 6), y, 0xFFD700, ft_itoa(shape->shape_id[SPHERE]), 1);
    }
    else if (shape->type == PLANE)
    {
        display(x += (16 * 6), y, 0xFFD700, "Plane", 0);
        display(x += (6 * 6), y, 0xFFD700, ft_itoa(shape->shape_id[PLANE]), 1);
    }
    else if (shape->type == CYLINDER)
    {
        display(x += (16 * 6), y, 0xFFD700, "Cylinder", 0);
        display(x += (9 * 6), y, 0xFFD700, ft_itoa(shape->shape_id[CYLINDER]), 1);
    }
    display(x += (4 * 6), y, 0x87CEFA, ">", 0);
    display(x += (3 * 6), y, 0xFFFFFF, "TAB : To Next Shape", 0);
}

static void display_shape_preset(int x, int y)
{
    display(x, y, 0x87CEFA, "Preset Shape Color >", 0);
    display(x + (22 * 6), y, 0xFFFFFF, "1 : Soft Dream", 0);
    display(x + (41 * 6), y, 0xFFFFFF, "2 : Sunset", 0);
    display(x + (56 * 6), y, 0xFFFFFF, "3 : Fire", 0);
    display(x + (69 * 6), y, 0xFFFFFF, "4 : Blue Style", 0);
    display(x + (88 * 6), y, 0xFFFFFF, "5 : Forest", 0);
    display(x + (103 * 6), y, 0xFFFFFF, "6 : Coffee", 0);
    if (s()->preset == 1)
        display(x + (22 * 6), y, 0xFFD700, "1 : Soft Dream", 0);
    if (s()->preset == 2)
        display(x + (41 * 6), y, 0xFFD700, "2 : Sunset", 0);
    if (s()->preset == 3)
        display(x + (56 * 6), y, 0xFFD700, "3 : Fire", 0);
    if (s()->preset == 4)
        display(x + (69 * 6), y, 0xFFD700, "4 : Blue Style", 0);
    if (s()->preset == 5)
        display(x + (88 * 6), y, 0xFFD700, "5 : Forest", 0);
    if (s()->preset == 6)
        display(x + (103 * 6), y, 0xFFD700, "6 : Coffee", 0);
}

void shape_menu(int x, int y)
{
    t_shape *shape;

    shape = s()->shapes->array[s()->select];
    display(x, y, 0xFFFFFF, "- Model Edit Mode -", 0);
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