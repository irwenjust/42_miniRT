#include "miniRT.h"

int	ft_keypress(int keycode)
{
	if (keycode == ESC)
		ft_quit();
	else if (keycode == W || keycode == UP)
		s()->camera.coordinate.y += 5;
	else if (keycode == S || keycode == DOWN)
		s()->camera.coordinate.y -= 5;
	else if (keycode == A || keycode == LEFT)
		s()->camera.coordinate.x -= 5;
	else if (keycode == D || keycode == RIGHT)
		s()->camera.coordinate.x += 5;
	else if (keycode == Q)
		s()->camera.coordinate.z += 5;
	else if (keycode == E)
		s()->camera.coordinate.z -= 5;
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