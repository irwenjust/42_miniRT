/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:03:26 by likong            #+#    #+#             */
/*   Updated: 2024/11/18 14:31:38 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief parse input string value into a vector format
 */
t_vector	parse_vector(char **strs)
{
	return ((t_vector){
		.x = ft_atod(strs[X]),
		.y = ft_atod(strs[Y]),
		.z = ft_atod(strs[Z])
	});
}

/**
 * @brief Check whether input vector are identical
 * fabs function in math.h return the absolute value of inputs
 */
bool	vector_compare(t_vector v1, t_vector v2)
{
	return (
		fabs(v1.x - v2.x) < 1e-8 &&
		fabs(v1.y - v2.y) < 1e-8 &&
		fabs(v1.z - v2.z) < 1e-8
	);
}

/**
 * @brief Calculate the cosine of the angle between two vectors
 */
inline double	vector_cos(t_vector v1, t_vector v2)
{
	return (vector_dot(v1, v2) / (vector_magnitude(v1) * vector_magnitude(v2)));
}
