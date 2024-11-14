/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:35:32 by yzhan             #+#    #+#             */
/*   Updated: 2024/11/13 16:35:33 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool is_intersect(t_shape *shape, t_ray *ray, t_hit *inter)
{
	if (shape->type == SPHERE)
		return (inter_sphere(&shape->data.sphere, ray, inter));
	if (shape->type == PLANE)
		return (inter_plane(&shape->data.plane, ray, inter));
	if (shape->type == CYLINDER)
		return (false);
	return (false);
}

