/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op_plus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:18:48 by likong            #+#    #+#             */
/*   Updated: 2024/11/27 21:00:42 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//magnitude, normalization, dot product, cross product

/**
 * @brief Compute the length of a given vector
 */
inline double	vector_magnitude(t_vector a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

/**
 * @brief normalize a given vector, convert it into a unit vector(length 1)
 * if the length of vector is too small, close to 0, return itself
 * if not, convert it.
 * 
 */
inline t_vector	vector_normalize(t_vector vec)
{
	double	ori_len;
	double	nor_len;

	ori_len = vector_magnitude(vec);
	if (ori_len > 1e-8)
	{
		nor_len = 1.0 / ori_len;
		return ((t_vector){vec.x * nor_len, vec.y * nor_len, vec.z * nor_len});
	}
	return (vec);
}

/**
 * @brief The result is a vector that perpendicular to both input vector,
 * so the return vector is perpendicular to the plane containing inputs vec.
 */
inline t_vector	vector_cross(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

/**
 * @brief Calculate a scalar quantity that measures the extent of 
 * two vector direct to the same direction (the aligned)
 * if the result is 1, means these two vector are parallel
 */
inline double	vector_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

inline t_vector	vector_scale(t_vector a, double scalar)
{
	return ((t_vector){a.x * scalar, a.y * scalar, a.z * scalar});
}
