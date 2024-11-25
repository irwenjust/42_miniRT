#include "miniRT.h"

void rotate_plane(t_key *keys, t_plane *plane)
{
	if (keys->key[U])
		plane->normal = vector_rotate(plane->normal, Z, ROTATE);
	else if (keys->key[O])
		plane->normal = vector_rotate(plane->normal, Z, (-ROTATE));
	else if (keys->key[J])
		plane->normal = vector_rotate(plane->normal, Y, -ROTATE);
	else if (keys->key[L])
		plane->normal = vector_rotate(plane->normal, Y, ROTATE);
	else if (keys->key[I])
		plane->normal = vector_rotate(plane->normal, X, -ROTATE);
	else if (keys->key[K])
		plane->normal = vector_rotate(plane->normal, X, ROTATE);
	printf("rotate plane\n");
}

void rotate_cylinder(t_key *keys, t_cylinder *cylinder)
{
	if (keys->key[U])
		cylinder->normal = vector_rotate(cylinder->normal, Z, ROTATE);
	else if (keys->key[O])
		cylinder->normal = vector_rotate(cylinder->normal, Z, (-ROTATE));
	else if (keys->key[J])
		cylinder->normal = vector_rotate(cylinder->normal, Y, -ROTATE);
	else if (keys->key[L])
		cylinder->normal = vector_rotate(cylinder->normal, Y, ROTATE);
	else if (keys->key[I])
		cylinder->normal = vector_rotate(cylinder->normal, X, -ROTATE);
	else if (keys->key[K])
		cylinder->normal = vector_rotate(cylinder->normal, X, ROTATE);
	cylinder->cap_u = vector_add(cylinder->center, vector_multiple(cylinder->normal, -cylinder->height / 2.0));
	cylinder->cap_b = vector_add(cylinder->center, vector_multiple(cylinder->normal, cylinder->height / 2.0));
	printf("rotate cylinder\n");
}
