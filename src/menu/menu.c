#include "miniRT.h"

void	display(int x, int y, int color, char *text)
{
	mlx_string_put(s()->win.mlx, s()->win.disp, x, y, color, text);
}

void display_menu()
{
    int y;

    y = HEIGHT * 0.9 + 20;
    mlx_put_image_to_window(s()->win.mlx, s()->win.disp, s()->win.menu, 0, (HEIGHT * 0.9));
    if (s()->menu.mode == VIEW)
    {
        display(10, y,  0xFFFFFF, "-View Mode-");
        display(10, (y + 20),  0xFFFFFF, "description...");
    }
    else if (s()->menu.mode == CAMERA)
        display(10, y,  0xFFFFFF, "-Camera Mode-");
    else if (s()->menu.mode == LIGHT)
        display(10, y,  0xFFFFFF, "-Light Mode-");
    else if (s()->menu.mode == SHAPE)
        display(10, y,  0xFFFFFF, "-Shape Mode-");
    else
        display(10, y,  0xFFFFFF, "-empty-");
}

void change_menu(t_mode mode)
{
	if	(s()->menu.mode != mode)
	{
		s()->menu.mode = mode;
		// render();
		display_menu();
		// printf("1 %s\n", MENUKEY);
	}
}