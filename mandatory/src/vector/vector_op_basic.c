/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op_basic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:34:35 by yzhan             #+#    #+#             */
/*   Updated: 2024/12/09 12:52:06 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//add, subtract, negat, multiple, divide

inline t_vector	vector_add(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

inline t_vector	vector_sub(t_vector v1, t_vector v2)
{
	return ((t_vector){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

inline t_vector	vector_scale(t_vector a, double scalar)
{
	return ((t_vector){a.x * scalar, a.y * scalar, a.z * scalar});
}

inline t_vector	vector_min(t_vector a, t_vector b)
{
	return ((t_vector){fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z)});
}

inline t_vector	vector_max(t_vector a, t_vector b)
{
	return ((t_vector){fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z)});
}
