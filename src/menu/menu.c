#include "miniRT.h"

//font width = 6, font height ~= 10

static void display_view_menu(int ori_x, int y)
{
    int x;

    x = ori_x;
    display(x, y,  0xFFFFFF, "- View Mode -");
    x = ori_x;
    display(x, y += 20,  0x87CEFA, "Preset Scenes >");
    display(x += (17 * 6), y,  0xFFFFFF, "1 : Scene 1");
    display(x += (16 * 6), y,  0xFFFFFF, "2 : Scene 2");
    display(x += (16 * 6), y,  0xFFFFFF, "3 : Scene 3");
    display(x += (16 * 6), y,  0xFFFFFF, "4 : Scene 4");
    display(x += (16 * 6), y,  0xFFFFFF, "5 : Scene 5");
    display(x += (16 * 6), y,  0xFFFFFF, "6 : Scene 6");
    x = ori_x;
    display(x, y += 40,  0x87CEFA, "Change Mode >");
    display(x += (15 * 6), y,  0xFFFFFF, "C : Enter [Camera Edit Mode]");
    display(x += (33 * 6), y,  0xFFFFFF, "B : Enter [LightSource Edit Mode]");
    display(x += (38 * 6), y,  0xFFFFFF, "M : Enter [Model Edit Mode]");
}

static void display_camera_menu(int ori_x, int y)
{
    int x;

    x = ori_x;
    display(x, y,  0xFFFFFF, "- Camera Edit Mode -");
    display(x, y += 20,  0x87CEFA, "Movement and Rotation >"); //+2
    display(x += (25 * 6), y,  0xFFFFFF, "WASD : Move Up/Left/Dowm/Right"); //+5
    display(x += (35 * 6), y,  0xFFFFFF, "QE : Move Forward/Backward");
    display(x += (31 * 6), y,  0xFFFFFF, "IJKL : Rotate Up/Left/Dowm/Right");
    x = ori_x;
    display(x, y += 20,  0x87CEFA, "Preset Camera >");
    display(x += (17 * 6), y,  0xFFFFFF, "1 : Front View");
    display(x += (19 * 6), y,  0xFFFFFF, "2 : Back View");
    display(x += (18 * 6), y,  0xFFFFFF, "3 : Top View");
    display(x += (17 * 6), y,  0xFFFFFF, "4 : Bottom View");
    display(x += (20 * 6), y,  0xFFFFFF, "5 : Left View");
    display(x += (18 * 6), y,  0xFFFFFF, "6 : Right View");
    x = ori_x;
    display(x, y += 20,  0x87CEFA, "Change Mode >");
    display(x += (15 * 6), y,  0xFFFFFF, "V : Enter [View Mode]");
    display(x += (26 * 6), y,  0xFFFFFF, "B : Enter [LightSource Edit Mode]");
    display(x += (38 * 6), y,  0xFFFFFF, "M : Enter [Model Edit Mode]");
}

static void display_light_menu(int ori_x, int y)
{
    int x;

    x = ori_x;
    display(x, y,  0xFFFFFF, "- LightSource Edit Mode -");
    x = ori_x;
    display(x, y += 20,  0x87CEFA, "Movement and Rotation >");
    display(x += (25 * 6), y,  0xFFFFFF, "WASD : Move Up/Left/Dowm/Right");
    display(x += (35 * 6), y,  0xFFFFFF, "QE : Move Forward/Backward");
    display(x += (31 * 6), y,  0xFFFFFF, "IJKL : Rotate Up/Left/Dowm/Right");
    x = ori_x;
    display(x, y += 20,  0x87CEFA, "Preset Light Color >");
    display(x += (22 * 6), y,  0xFFFFFF, "1 : Red"); //warm
    display(x += (12 * 6), y,  0xFFFFFF, "2 : Yellow"); //cool
    display(x += (15 * 6), y,  0xFFFFFF, "3 : Blue"); //sunset
    display(x += (13 * 6), y,  0xFFFFFF, "4 : Green"); //moonlight
    display(x += (14 * 6), y,  0xFFFFFF, "5 : Pink"); //cyberpunk
    display(x += (13 * 6), y,  0xFFFFFF, "6 : Purple"); //disco
    x = ori_x;
    display(x, y += 20,  0x87CEFA, "Change Mode >");
    display(x += (15 * 6), y,  0xFFFFFF, "V : Enter [View Mode]");
    display(x += (26 * 6), y,  0xFFFFFF, "C : Enter [Camera Edit Mode]");
    display(x += (33 * 6), y,  0xFFFFFF, "M : Enter [Model Edit Mode]");
}

void display_shape(int x, int y)
{
    t_shape *shape;

    printf("%i\n", s()->select);
    shape = s()->shapes->array[s()->select];
    display(x += (24 * 6), y,  0xFFD700, "Current Shape:");
    if (shape->type == SPHERE)
    {
        display(x += (16 * 6), y,  0xFFD700, "Sphere");
        display(x += (7 * 6), y,  0xFFD700, ft_itoa(shape->sp_id + 1));
    }
    else if (shape->type == PLANE)
    {
        display(x += (16 * 6), y,  0xFFD700, "Plane");
        display(x += (6 * 6), y,  0xFFD700, ft_itoa(shape->pl_id + 1));
    }
    else if (shape->type == CYLINDER)
    {
        display(x += (16 * 6), y,  0xFFD700, "Cylinder");
        display(x += (9 * 6), y,  0xFFD700, ft_itoa(shape->cy_id + 1));
    }
}

static void display_model_menu(int ori_x, int y)
{
    int x;

    x = ori_x;
    display(x, y,  0xFFFFFF, "- Model Edit Mode -");
    display_shape(ori_x, y);
    x = ori_x;
    display(x, y += 20,  0x87CEFA, "Movement and Rotation >");
    display(x += (25 * 6), y,  0xFFFFFF, "WASD : Move Up/Left/Dowm/Right");
    display(x += (35 * 6), y,  0xFFFFFF, "QE : Move Forward/Backward");
    display(x += (31 * 6), y,  0xFFFFFF, "IJKL : Rotate Up/Left/Dowm/Right");
    x = ori_x;
    display(x, y += 20,  0x87CEFA, "Preset Shape Color >");
    display(x += (22 * 6), y,  0xFFFFFF, "1 : Red");
    display(x += (12 * 6), y,  0xFFFFFF, "2 : Yellow");
    display(x += (15 * 6), y,  0xFFFFFF, "3 : Blue");
    display(x += (13 * 6), y,  0xFFFFFF, "4 : Green");
    display(x += (14 * 6), y,  0xFFFFFF, "5 : Pink");
    display(x += (13 * 6), y,  0xFFFFFF, "6 : Purple");
    x = ori_x;
    display(x, y += 20,  0x87CEFA, "Change Mode >");
    display(x += (15 * 6), y,  0xFFFFFF, "V : Enter [View Mode]");
    display(x += (26 * 6), y,  0xFFFFFF, "C : Enter [Camera Edit Mode]");
    display(x += (33 * 6), y,  0xFFFFFF, "B : Enter [LightSource Edit Mode]");
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

