

#include "miniRT_bonus.h"

//add, subtract, negat, multiple, divide

inline t_vector	vector_add(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

inline t_vector	vector_sub(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

inline t_vector	vector_multiple(t_vector v1, double scalar)
{
	return ((t_vector){v1.x * scalar, v1.y * scalar, v1.z * scalar});
}

inline t_vector	vector_min(t_vector a, t_vector b)
{
	return ((t_vector){fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z)});
}

inline t_vector	vector_max(t_vector a, t_vector b)
{
	return ((t_vector){fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z)});
}
