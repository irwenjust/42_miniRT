#include "miniRT.h"

//font width = 6, font height ~= 10
void display_menu()
{
    int y;

    y = HEIGHT * 0.88 + 20;
    mlx_put_image_to_window(s()->win.mlx, s()->win.disp, s()->win.menu, 0, (HEIGHT * 0.88));
    if (s()->menu == VIEW)
        view_menu(10, y);
    else if (s()->menu == CAMERA)
        camera_menu(10, y);
    else if (s()->menu == LIGHT)
        light_menu(10, y);
    else if (s()->menu == SHAPE)
        shape_menu(10, y);
    
}

