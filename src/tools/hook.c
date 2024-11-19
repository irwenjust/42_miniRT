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
	else if (keycode == I)
		s()->camera.normal = vector_rotate(s()->camera.normal, Z, ROTATE);
	else if (keycode == K)
		s()->camera.normal = vector_rotate(s()->camera.normal, Z, (-ROTATE));
	else if (keycode == J)
		s()->camera.normal = vector_rotate(s()->camera.normal, Y, -ROTATE);
	else if (keycode == L)
		s()->camera.normal = vector_rotate(s()->camera.normal, Y, ROTATE);
	else if (keycode == U)
		s()->camera.normal = vector_rotate(s()->camera.normal, X, -ROTATE);
	else if (keycode == O)
		s()->camera.normal = vector_rotate(s()->camera.normal, X, ROTATE);
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