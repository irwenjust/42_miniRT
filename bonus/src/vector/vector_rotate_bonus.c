

#include "miniRT_bonus.h"

t_vector	vector_rotate(t_vector vec, int axis, double angle)
{
	t_vector	res;

	res = vec;
	if (axis == X)
	{
		res.y = vec.y * cos(angle) - vec.z * sin(angle);
		res.z = vec.y * sin(angle) + vec.z * cos(angle);
		printf("here: x: %f, y: %f, z: %f\n", res.x, res.y, res.z);
	}
	else if (axis == Y)
	{
		res.x = vec.x * cos(angle) + vec.z * sin(angle);
		res.z = -vec.x * sin(angle) + vec.z * cos(angle);
		printf("here: x: %f, y: %f, z: %f\n", res.x, res.y, res.z);
	}
	else if (axis == Z)
	{
		res.x = vec.x * cos(angle) - vec.y * sin(angle);
		res.y = vec.x * sin(angle) + vec.y * cos(angle);
		printf("here: x: %f, y: %f, z: %f\n", res.x, res.y, res.z);
		printf("vec: x: %f, y: %f\n", vec.x, vec.y);
	}
	return (vector_normalize(res));
}
