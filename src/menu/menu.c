#include "miniRT.h"

//width * 7, height * 20*line
static void display_view_menu(int x, int y)
{
    display(x, y,  0xFFFFFF, "- View Mode -");
    display(x, y + 60,  0xFFFFFF, "C : Enter [ Camera Edit Mode ]");
    display(x + 210, y + 60,  0xFFFFFF, "B : Enter [ LightSource Edit Mode ]");
    display(x + 455, y + 60,  0xFFFFFF, "M : Enter [ Model Edit Mode ]");
}

static void display_camera_menu(int x, int y)
{
    display(x, y,  0xFFFFFF, "- Camera Edit Mode -");
    display(x, y + 20,  0xFFFFFF, "Movement and Rotation >");
    display(x + 175, y + 20,  0xFFFFFF, "WASD : Move Up/Left/Dowm/Right");
    display(x + 385, y + 20,  0xFFFFFF, "QE : Move forward/backward");
    display(x + 560, y + 20,  0xFFFFFF, "IJKL : Rotate Up/Left/Dowm/Right");
    display(x, y + 40,  0xFFFFFF, "Preset Camera >");
    display(x + 119, y + 40,  0xFFFFFF, "1 : Front View");
    display(x + 210, y + 40,  0xFFFFFF, "2 : Back View");
    display(x + 294, y + 40,  0xFFFFFF, "3 : Top View");
    display(x + 371, y + 40,  0xFFFFFF, "4 : Bottom View");
    display(x + 469, y + 40,  0xFFFFFF, "5 : Left View");
    display(x + 553, y + 40,  0xFFFFFF, "6 : Right View");
    display(x, y + 60,  0xFFFFFF, "Change Mode >");
    display(x + 105, y + 60,  0xFFFFFF, "V : Enter [ View Mode ]");
    display(x + 266, y + 60,  0xFFFFFF, "B : Enter [ LightSource Edit Mode ]");
    display(x + 511, y + 60,  0xFFFFFF, "M : Enter [ Model Edit Mode ]");
}

static void display_light_menu(int x, int y)
{
    display(x, y,  0xFFFFFF, "- LightSource Edit Mode -");
    display(x, y + 60,  0xFFFFFF, "V : Enter [ View Mode ]");
    display(x + 161, y + 60,  0xFFFFFF, "C : Enter [ Camera Edit Mode ]");
    display(x + 371, y + 60,  0xFFFFFF, "M : Enter [ Model Edit Mode ]");
}

static void display_model_menu(int x, int y)
{
    display(x, y,  0xFFFFFF, "- Model Edit Mode -");
    display(x, y + 60,  0xFFFFFF, "V : Enter [ View Mode ]");
    display(x + 161, y + 60,  0xFFFFFF, "C : Enter [ Camera Edit Mode ]");
    display(x + 371, y + 60,  0xFFFFFF, "B : Enter [ LightSource Edit Mode ]");
}

void display_menu()
{
    int y;

    y = HEIGHT * 0.9 + 20;
    mlx_put_image_to_window(s()->win.mlx, s()->win.disp, s()->win.menu, 0, (HEIGHT * 0.9));
    if (s()->menu.mode == VIEW)
        display_view_menu(10, y);
    else if (s()->menu.mode == CAMERA)
        display_camera_menu(10, y);
    else if (s()->menu.mode == LIGHT)
        display_light_menu(10, y);
    else if (s()->menu.mode == SHAPE)
        display_model_menu(10, y);
    // else
    //     display(10, y,  0xFFFFFF, "-empty-");
}

