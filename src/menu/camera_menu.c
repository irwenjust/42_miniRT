#include "miniRT.h"

static void display_camera_preset(int x, int y)
{
    display(x, y, 0x87CEFA, "Preset Camera >", 0);
    display(x + (17 * 6), y, 0xFFFFFF, "1 : Front View", 0);
    display(x + (36 * 6), y, 0xFFFFFF, "2 : Back View", 0);
    display(x + (54 * 6), y, 0xFFFFFF, "3 : Top View", 0);
    display(x + (71 * 6), y, 0xFFFFFF, "4 : Bottom View", 0);
    display(x + (91 * 6), y, 0xFFFFFF, "5 : Left View", 0);
    display(x + (109 * 6), y, 0xFFFFFF, "6 : Right View", 0);
    if (s()->preset == 1)
        display(x + (17 * 6), y, 0xFFD700, "1 : Front View", 0);
    if (s()->preset == 2)
        display(x + (36 * 6), y, 0xFFD700, "2 : Back View", 0);
    if (s()->preset == 3)
        display(x + (54 * 6), y, 0xFFD700, "3 : Top View", 0);
    if (s()->preset == 4)
        display(x + (71 * 6), y, 0xFFD700, "4 : Bottom View", 0);
    if (s()->preset == 5)
        display(x + (91 * 6), y, 0xFFD700, "5 : Left View", 0);
    if (s()->preset == 6)
        display(x + (109 * 6), y, 0xFFD700, "6 : Right View", 0);
}

void camera_menu(int x, int y)
{
    display(x, y, 0xFFFFFF, "- Camera Edit Mode -", 0);
    display_move_rotate_size(x, y + 20);
    display_camera_preset(x, y + 40);
    display_mode(x, y + 80);
}