/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:29:02 by likong            #+#    #+#             */
/*   Updated: 2024/10/24 17:51:39 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_viewport()
{
	s()->w_view = tan(RADIAN(s()->camera.fov / 2.0));
	s()->h_view = s()->w_view * SCALE;
	s()->vec_w = normalize_vector(vector_cross(s()->camera.normal,UPVECTOR));
	s()->vec_h = normalize_vector(vector_cross(s()->camera.normal, s()->vec_w));
	s()->vec_w = normalize_vector(vector_cross(s()->camera.normal, s()->vec_h));
}
