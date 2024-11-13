/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:03:26 by likong            #+#    #+#             */
/*   Updated: 2024/10/23 18:19:13 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//??????????
double	vector_len(t_vector a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

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
