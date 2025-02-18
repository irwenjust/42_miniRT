/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:24:20 by likong            #+#    #+#             */
/*   Updated: 2025/02/18 09:24:23 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
