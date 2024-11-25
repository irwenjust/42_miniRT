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
	// print_camera(&s()->camera);
    printf("move camera\n");
}

static void move_light(t_key *keys, t_light *light)
{
	if (keys->key[W])
		light->point.y += 0.3;
	else if (keys->key[S])
		light->point.y -= 0.3;
	else if (keys->key[A])
		light->point.x -= 0.3;
	else if (keys->key[D])
		light->point.x += 0.3;
	else if (keys->key[Q])
		light->point.z += 0.3;
	else if (keys->key[E])
		light->point.z -= 0.3;
    control_frame_rate();
    printf("move light\n");
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
	else if (s()->menu.mode == LIGHT)
		move_light(keys, s()->light->array[0]);
    else if (s()->menu.mode == SHAPE)
        move_shape(keys, s()->shapes->array[s()->select]);
}

