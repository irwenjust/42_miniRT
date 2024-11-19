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




t_vector	parse_vector(char **strs)
{
	return ((t_vector){
		.x = ft_atod(strs[X]),
		.y = ft_atod(strs[Y]),
		.z = ft_atod(strs[Z])
	});
}

inline t_vector	new_vector(double x, double y, double z)
{
	return ((t_vector){x, y, z});
}

bool	vector_compare(t_vector v1, t_vector v2)
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}
