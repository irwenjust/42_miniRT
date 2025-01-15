/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 10:30:03 by likong            #+#    #+#             */
/*   Updated: 2025/01/15 11:44:11 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static void	change_normal(t_hit *hit, double *pd_u, double *pd_v)
{
	double	height;
	double	step_u;
	double	step_v;

	height = uv_get_color(hit->shape->bmp, hit->u, hit->v).red;
	step_u = 1.0 / hit->shape->bmp->width;
	step_v = 1.0 / hit->shape->bmp->height;
	*pd_u = uv_get_color(hit->shape->bmp, hit->u + step_u, hit->v).red;
	*pd_v = uv_get_color(hit->shape->bmp, hit->u, hit->v + step_v).red;
	*pd_u = (*pd_u - height) / step_u;
	*pd_v = (*pd_v - height) / step_v;
}

//pd_u: partial derivative of the bump map height with respect to the texture
//coordinate u
void	check_bump(t_hit *hit)
{
	double		pd_u;
	double		pd_v;
	t_shape		*shape;
	t_vector	adjust_normal;

	shape = hit->shape;
	if (shape->bmp)
	{
		change_normal(hit, &pd_u, &pd_v);
		adjust_normal = vector_add(vector_scale(shape->u_axis, -pd_u),
			vector_scale(shape->v_axis, -pd_v));
		adjust_normal = vector_scale(adjust_normal, 3);
		hit->hit_normal = vector_add(hit->hit_normal, adjust_normal);
		hit->hit_normal = vector_normalize(hit->hit_normal);
	}
}
