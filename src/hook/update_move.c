#include "miniRT.h"

static void move_camera(t_key *keys)
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
    printf("move canera\n");
}

static void move_shape(t_key *keys, t_shape *shape)
{
	if (shape->type == SPHERE)
		move_sphere(keys, &(shape->data.sphere));
	else if (shape->type == PLANE)
		move_plane(keys, &(shape->data.plane));
	else if (shape->type == CYLINDER)
		move_cylinder(keys, &(shape->data.cylinder));
	print_shape(shape);
    control_frame_rate();
}

void update_move(t_key *keys)
{
    if (s()->menu.mode == CAMERA)
        move_camera(keys);
    if (s()->menu.mode == SHAPE)
        move_shape(keys, s()->shapes->array[s()->select]);
}

