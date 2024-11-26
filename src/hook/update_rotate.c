#include "miniRT.h"

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
	// print_camera(&s()->camera);
    printf("rotate\n");
}

static void rotate_shape(t_key *keys, t_shape *shape)
{
	if (shape->type == PLANE)
		rotate_plane(keys, &(shape->data.plane));
	else if (shape->type == CYLINDER)
		rotate_cylinder(keys, &(shape->data.cylinder));
    control_frame_rate();
}

void update_rotate(t_key *keys)
{
    if (s()->menu == CAMERA)
        rotate_camera(keys);
    if (s()->menu == SHAPE)
        rotate_shape(keys, s()->shapes->array[s()->select]);
}
