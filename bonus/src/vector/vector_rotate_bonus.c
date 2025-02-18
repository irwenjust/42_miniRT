/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotate_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:03:06 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/18 09:24:12 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_vector	vector_rotate(t_vector vec, int axis, double angle)
{
	t_vector	res;

	res = vec;
	if (axis == X)
	{
		res.y = vec.y * cos(angle) - vec.z * sin(angle);
		res.z = vec.y * sin(angle) + vec.z * cos(angle);
	}
	else if (axis == Y)
	{
		res.x = vec.x * cos(angle) + vec.z * sin(angle);
		res.z = -vec.x * sin(angle) + vec.z * cos(angle);
	}
	else if (axis == Z)
	{
		res.x = vec.x * cos(angle) - vec.y * sin(angle);
		res.y = vec.x * sin(angle) + vec.y * cos(angle);
	}
	return (vector_normalize(res));
}
