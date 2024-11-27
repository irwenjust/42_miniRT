#include "miniRT.h"

//font width = 6, font height ~= 10

static void view_menu(int ori_x, int y)
{
    int x;

    display(ori_x, y,  0xFFFFFF, "- View Mode -");
    display(ori_x, y += 20,  0x87CEFA, "Preset Scenes >");
    x = ori_x;
    display(x += (17 * 6), y,  0xFFFFFF, "1 : Scene 1");
    display(x += (16 * 6), y,  0xFFFFFF, "2 : Scene 2");
    display(x += (16 * 6), y,  0xFFFFFF, "3 : Scene 3");
    display(x += (16 * 6), y,  0xFFFFFF, "4 : Scene 4");
    display(x += (16 * 6), y,  0xFFFFFF, "5 : Scene 5");
    display(x += (16 * 6), y,  0xFFFFFF, "6 : Scene 6");
    display_mode(ori_x, y += 40);
}

static void camera_menu(int ori_x, int y)
{
    int x;

    display(ori_x, y,  0xFFFFFF, "- Camera Edit Mode -");
    display_move_rotate(ori_x, y += 20);
    display(ori_x, y += 20,  0x87CEFA, "Preset Camera >");
    x = ori_x;
    display(x += (17 * 6), y,  0xFFFFFF, "1 : Front View");
    display(x += (19 * 6), y,  0xFFFFFF, "2 : Back View");
    display(x += (18 * 6), y,  0xFFFFFF, "3 : Top View");
    display(x += (17 * 6), y,  0xFFFFFF, "4 : Bottom View");
    display(x += (20 * 6), y,  0xFFFFFF, "5 : Left View");
    display(x += (18 * 6), y,  0xFFFFFF, "6 : Right View");
    display_mode(ori_x, y += 20);
}

static void light_menu(int ori_x, int y)
{
    int x;

    display(ori_x, y,  0xFFFFFF, "- LightSource Edit Mode -");
    x = ori_x;
    display(x += (30 * 6), y,  0xFFD700, "Current Light:");
    display(x += (16 * 6), y,  0xFFD700, "Light");
    display(x += (6 * 6), y,  0xFFD700, ft_itoa(s()->select)); 
    display_move_rotate(ori_x, y += 20);
    display(ori_x, y += 20,  0x87CEFA, "Preset Light Color >");
    x = ori_x;
    display(x += (22 * 6), y,  0xFFFFFF, "1 : Red"); //warm
    display(x += (12 * 6), y,  0xFFFFFF, "2 : Yellow"); //cool
    display(x += (15 * 6), y,  0xFFFFFF, "3 : Blue"); //sunset
    display(x += (13 * 6), y,  0xFFFFFF, "4 : Green"); //moonlight
    display(x += (14 * 6), y,  0xFFFFFF, "5 : Pink"); //cyberpunk
    display(x += (13 * 6), y,  0xFFFFFF, "6 : Purple"); //disco
    display_mode(ori_x, y += 20);
}

static void shape_menu(int ori_x, int y)
{
    int x;

    display(ori_x, y,  0xFFFFFF, "- Model Edit Mode -");
    display_shape(ori_x + (24 * 6), y);
    display_move_rotate(ori_x, y += 20);
    display(ori_x, y += 20,  0x87CEFA, "Preset Shape Color >");
    x = ori_x;
    display(x += (22 * 6), y,  0xFFFFFF, "1 : Red");
    display(x += (12 * 6), y,  0xFFFFFF, "2 : Yellow");
    display(x += (15 * 6), y,  0xFFFFFF, "3 : Blue");
    display(x += (13 * 6), y,  0xFFFFFF, "4 : Green");
    display(x += (14 * 6), y,  0xFFFFFF, "5 : Pink");
    display(x += (13 * 6), y,  0xFFFFFF, "6 : Purple");
    display_color(x += (20 * 6), y);
    display_mode(ori_x, y += 20);
}

void display_menu()
{
    int y;

    y = HEIGHT * 0.9 + 20;
    mlx_put_image_to_window(s()->win.mlx, s()->win.disp, s()->win.menu, 0, (HEIGHT * 0.9));
    if (s()->menu == VIEW)
        view_menu(10, y);
    else if (s()->menu == CAMERA)
        camera_menu(10, y);
    else if (s()->menu == LIGHT)
        light_menu(10, y);
    else if (s()->menu == SHAPE)
        shape_menu(10, y);
}

