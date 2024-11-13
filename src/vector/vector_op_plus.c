/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op_plus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:18:48 by likong            #+#    #+#             */
/*   Updated: 2024/10/24 14:48:07 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//magnitude, normalization, dot product, cross product

inline t_vector	vector_normalize(t_vector a)
{
	double	ori_len;
	double	adj_len;

	ori_len = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	if (ori_len > 1e-8)  //maybe need adjust this later
	{
		adj_len = 1.0 / ori_len;
		return ((t_vector){a.x * adj_len, a.y * adj_len, a.z * adj_len});
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
