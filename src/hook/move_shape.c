#include "miniRT.h"

void move_sphere(t_key *keys, t_sphere *sphere)
{
	if (keys->key[W])
		sphere->center.y += 0.3;
	else if (keys->key[S])
		sphere->center.y -= 0.3;
	else if (keys->key[A])
		sphere->center.x -= 0.3;
	else if (keys->key[D])
		sphere->center.x += 0.3;
	else if (keys->key[Q])
		sphere->center.z += 0.3;
	else if (keys->key[E])
		sphere->center.z -= 0.3;
	printf("move sphere\n");
}

void move_plane(t_key *keys, t_plane *plane)
{
	if (keys->key[W])
		plane->center.y += 0.3;
	else if (keys->key[S])
		plane->center.y -= 0.3;
	else if (keys->key[A])
		plane->center.x -= 0.3;
	else if (keys->key[D])
		plane->center.x += 0.3;
	else if (keys->key[Q])
		plane->center.z += 0.3;
	else if (keys->key[E])
		plane->center.z -= 0.3;
	printf("move plane\n");
}

void move_cylinder(t_key *keys, t_cylinder *cylinder)
{
	if (keys->key[W])
	{
		printf("move W\n");
		cylinder->center.y += 0.3;
	}
	else if (keys->key[S])
		cylinder->center.y -= 0.3;
	else if (keys->key[A])
		cylinder->center.x -= 0.3;
	else if (keys->key[D])
		cylinder->center.x += 0.3;
	else if (keys->key[Q])
		cylinder->center.z += 0.3;
	else if (keys->key[E])
		cylinder->center.z -= 0.3;
	printf("move cylinder\n");
}

