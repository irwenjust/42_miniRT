/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op_plus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:18:48 by likong            #+#    #+#             */
/*   Updated: 2024/11/18 15:27:29 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//magnitude, normalization, dot product, cross product

inline double	vector_len(t_vector a)
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
	double	adj_len;

	ori_len = vector_len(vec);
	if (ori_len > 1e-8)
	{
		adj_len = 1.0 / ori_len;
		return ((t_vector){vec.x * adj_len, vec.y * adj_len, vec.z * adj_len});
	}
	return (a);
}

inline t_vector	vector_cross(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

inline double	vector_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

inline double	vector_cos(t_vector v1, t_vector v2)
{
	return (vector_dot(v1, v2) / (vector_len(v1) * vector_len(v2)));
}
