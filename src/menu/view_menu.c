#include "miniRT.h"

static void display_view_preset(int x, int y)
{
    display(x, y, 0x87CEFA, "Preset Scenes >", 0);
    display(x + (17 * 6), y, 0xFFFFFF, "1 : Scene 1", 0);
    display(x + (33 * 6), y, 0xFFFFFF, "2 : Scene 2", 0);
    display(x + (49 * 6), y, 0xFFFFFF, "3 : Scene 3", 0);
    display(x + (65 * 6), y, 0xFFFFFF, "4 : Scene 4", 0);
    display(x + (81 * 6), y, 0xFFFFFF, "5 : Scene 5", 0);
    display(x + (97 * 6), y, 0xFFFFFF, "6 : Scene 6", 0);
    if (s()->preset == 1)
        display(x + (17 * 6), y, 0xFFD700, "1 : Scene 1", 0);
    if (s()->preset == 2)
        display(x + (33 * 6), y, 0xFFD700, "2 : Scene 2", 0);
    if (s()->preset == 3)
        display(x + (49 * 6), y, 0xFFD700, "3 : Scene 3", 0);
    if (s()->preset == 4)
        display(x + (65 * 6), y, 0xFFD700, "4 : Scene 4", 0);
    if (s()->preset == 5)
        display(x + (81 * 6), y, 0xFFD700, "5 : Scene 5", 0);
    if (s()->preset == 6)
        display(x + (97 * 6), y, 0xFFD700, "6 : Scene 6", 0);
}

void view_menu(int x, int y)
{
    display(x, y, 0xFFFFFF, "- View Mode -", 0);
    display(x, y + 20, 0x87CEFA, "Ambient ", 0);
    display_color(x + (8 * 6), y + 20, &(s()->ambient.color));
    display(x + (96 * 6), y + 20, 0x87CEFA, "Ambient ", 0);
    display_brightness(x + (104 * 6), y + 20, s()->ambient.brightness);
    display_view_preset(x, y + 40);
    display_mode(x, y + 80);
}