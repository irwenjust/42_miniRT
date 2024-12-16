#include "miniRT.h"

// static void display_light(int x, int y)
// {
//     display(x, y, 0xFFD700, "Current Light:");
//     display(x += (16 * 6), y, 0xFFD700, "Light");
//     display(x += (6 * 6), y, 0xFFD700, ft_itoa(s()->select)); 
// }

static void display_light_preset(int x, int y)
{
    display(x, y, 0x87CEFA, "Preset Light Color & Brightness >", 0);
    display(x + (35 * 6), y, 0xFFFFFF, "1 : Warm White", 0);
    display(x + (54 * 6), y, 0xFFFFFF, "2 : Cold White", 0);
    display(x + (73 * 6), y, 0xFFFFFF, "3 : Sunset", 0);
    display(x + (88 * 6), y, 0xFFFFFF, "4 : Moonlight", 0);
    display(x + (106 * 6), y, 0xFFFFFF, "5 : Cyberpunk", 0);
    display(x + (124 * 6), y, 0xFFFFFF, "6 : Toxic", 0);
    if (s()->preset == 1)
        display(x + (35 * 6), y, 0xFFD700, "1 : Warm White", 0);
    if (s()->preset == 2)
        display(x + (54 * 6), y, 0xFFD700, "2 : Cold White", 0);
    if (s()->preset == 3)
        display(x + (73 * 6), y, 0xFFD700, "3 : Sunset", 0);
    if (s()->preset == 4)
        display(x + (88 * 6), y, 0xFFD700, "4 : Moonlight", 0);
    if (s()->preset == 5)
        display(x + (106 * 6), y, 0xFFD700, "5 : Cyberpunk", 0);
    if (s()->preset == 6)
        display(x + (124 * 6), y, 0xFFD700, "6 : Toxic", 0);
}

void light_menu(int x, int y)
{
    t_light *light;

    light = s()->light->array[s()->select];
    display(x, y, 0xFFFFFF, "- LightSource Edit Mode -", 0);
    // display_light(x + (30 * 6), y);
    display_move_rotate_size(x, y + 20);
    display_color(x, y + 40, &light->color);
    display_brightness(x + (96 * 6), y + 40, light->brightness);
    display_light_preset(x, y + 60);
    display_mode(x, y + 80);
}