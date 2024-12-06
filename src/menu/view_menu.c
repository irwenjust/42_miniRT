#include "miniRT.h"

static void display_view_preset(int x, int y)
{
    display(x, y, 0x87CEFA, "Preset Scenes >");
    display(x + (17 * 6), y, 0xFFFFFF, "1 : Scene 1");
    display(x + (33 * 6), y, 0xFFFFFF, "2 : Scene 2");
    display(x + (49 * 6), y, 0xFFFFFF, "3 : Scene 3");
    display(x + (65 * 6), y, 0xFFFFFF, "4 : Scene 4");
    display(x + (81 * 6), y, 0xFFFFFF, "5 : Scene 5");
    display(x + (97 * 6), y, 0xFFFFFF, "6 : Scene 6");
    if (s()->preset == 1)
        display(x + (17 * 6), y, 0xFFD700, "1 : Scene 1");
    if (s()->preset == 2)
        display(x + (33 * 6), y, 0xFFD700, "2 : Scene 2");
    if (s()->preset == 3)
        display(x + (49 * 6), y, 0xFFD700, "3 : Scene 3");
    if (s()->preset == 4)
        display(x + (65 * 6), y, 0xFFD700, "4 : Scene 4");
    if (s()->preset == 5)
        display(x + (81 * 6), y, 0xFFD700, "5 : Scene 5");
    if (s()->preset == 6)
        display(x + (97 * 6), y, 0xFFD700, "6 : Scene 6");
}

void view_menu(int x, int y)
{
    display(x, y, 0xFFFFFF, "- View Mode -");
    display_view_preset(x, y + 20);
    display_mode(x, y + 80);
}