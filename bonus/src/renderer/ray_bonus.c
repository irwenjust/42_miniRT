

#include "miniRT_bonus.h"

/**
 * @brief Generate a ray starts from camera position to viewport point
 * Main steps:
 * 		1-calculate the viewport point offset to viewport original point,
 * 		2-map the viewport point to camera direction, relative coordinates,
 * 		3-add the viewport point to camera normalized coordinates
 * 		  to get the absolute position in 3D world,
 * 		4-set a normalized ray, start from camera
 * 		5-subtrat tmp by ray start point to get the vector from camera to
 * 		  viewport point, then normalized it to get its direction.
 * 
 * @param cur The normalized 3D coordinates of viewport point
 * @param horizontal The horizontal offset of current view point
 * @param vertical The vertival offset of current view point
 * @param tmp The tmp vector used in the operation
 * @param ray The ray from camera to view point
 */
t_ray	make_ray(t_vector cur)
{
	t_vector	horizontal;
	t_vector	vertical;
	t_vector	tmp;
	t_ray		ray;

	horizontal = vector_multiple(s()->normal_w, cur.x * s()->view_w);
	vertical = vector_multiple(s()->normal_h, cur.y * s()->view_h);
	tmp = vector_add(vertical, horizontal);
	tmp = vector_add(tmp, s()->camera.normal);
	tmp = vector_add(tmp, s()->camera.coordinate);
	ray.start = s()->camera.coordinate;
	ray.normal = vector_normalize(vector_sub(tmp, ray.start));
	ray.inv_start = (t_vector){1.0 / ray.normal.x,
		1.0 / ray.normal.y, 1.0 / ray.normal.z};
	return (ray);
}

/**
 * @brief Calculate a point along ray based on a given distance
 * the equation is R(t) = O + tD
 */
inline t_vector	point_on_ray(t_ray *ray, double t)
{
	return (vector_add(ray->start, vector_multiple(ray->normal, t)));
}
