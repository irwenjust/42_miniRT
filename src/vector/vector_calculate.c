/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calculate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:18:48 by likong            #+#    #+#             */
/*   Updated: 2024/10/23 18:13:03 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

inline t_vector	normalize_vector(t_vector a)
{
	double	ori_len;
	double	adj_len;

	ori_len = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	if (ori_len > 1e-8)  //maybe need adjust this later
	{
		adj_len = 1.0 / ori_len;
		return ((t_vector){a.x * adj_len, a.y * adj_len, a.z * adj_len});
	}
	return (a);
}
