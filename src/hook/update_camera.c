#include "miniRT.h"

void move_camera(t_key *keys)
{
	if (keys->key[W])
		s()->camera.coordinate.y += 0.3;
	else if (keys->key[S])
		s()->camera.coordinate.y -= 0.3;
	else if (keys->key[A])
		s()->camera.coordinate.x -= 0.3;
	else if (keys->key[D])
		s()->camera.coordinate.x += 0.3;
	else if (keys->key[Q])
		s()->camera.coordinate.z += 0.3;
	else if (keys->key[E])
		s()->camera.coordinate.z -= 0.3;
    control_frame_rate();
    printf("move\n");
}

void rotate_camera(t_key *keys)
{
	if (keys->key[U])
		s()->camera.normal = vector_rotate(s()->camera.normal, Z, ROTATE);
	else if (keys->key[O])
		s()->camera.normal = vector_rotate(s()->camera.normal, Z, (-ROTATE));
	else if (keys->key[J])
		s()->camera.normal = vector_rotate(s()->camera.normal, Y, -ROTATE);
	else if (keys->key[L])
		s()->camera.normal = vector_rotate(s()->camera.normal, Y, ROTATE);
	else if (keys->key[I])
		s()->camera.normal = vector_rotate(s()->camera.normal, X, -ROTATE);
	else if (keys->key[K])
		s()->camera.normal = vector_rotate(s()->camera.normal, X, ROTATE);
    control_frame_rate();
    printf("rotate\n");
}