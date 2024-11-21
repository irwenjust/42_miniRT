#include "miniRT.h"

void	display(int x, int y, int color, char *text)
{
	mlx_string_put(s()->win.mlx, s()->win.disp, x, y, color, text);
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