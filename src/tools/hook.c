#include "miniRT.h"

int	ft_keypress(int keycode)
{
	if (keycode == ESC)
		ft_quit();
	//why dra_image here???
	//draw_image();
	render();
	return (keycode);
}

int	ft_quit()  //may change to void
{
	delete_scene();
	exit(SUCCESS);
}