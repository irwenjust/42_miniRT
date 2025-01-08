/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:27:00 by likong            #+#    #+#             */
/*   Updated: 2025/01/08 12:38:05 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	check_hit_normal(t_hit *hit)
{
	if (hit->shape->type == PLANE)
		hit->hit_normal = hit->shape->data.plane.normal;
	if (vector_dot(hit->ray.normal, hit->hit_normal) > 0)
	{
		hit->check_hit = true;
		hit->hit_normal = vector_scale(hit->hit_normal, -1);
	}
}
