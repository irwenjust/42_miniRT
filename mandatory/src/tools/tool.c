/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:15:24 by likong            #+#    #+#             */
/*   Updated: 2025/02/17 11:45:36 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_shape	**shapes_to_arr(t_shape **shapes)
{
	t_shape	**res;
	int		i;

	i = -1;
	res = ft_calloc(s()->shapes->size, sizeof(t_shape *));
	while (shapes[++i])
		res[i] = shapes[i];
	return (res);
}

void	ft_swap_d(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

t_hit	init_hit(void)
{
	static t_hit	hit;
	static bool		init = true;

	if (init)
	{
		ft_bzero(&hit, sizeof(t_hit));
		hit.color = hex_to_color(BACKGROUND);
		hit.distance = INFINITY;
		hit.shape = NULL;
		init = false;
	}
	return (hit);
}

double	calculate_radius(double angle)
{
	return ((angle * PI) / 180.0);
}
