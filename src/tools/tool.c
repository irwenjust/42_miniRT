/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:15:24 by likong            #+#    #+#             */
/*   Updated: 2024/11/28 13:42:05 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_shape	**shapes_to_arr(t_shape **shapes)
{
	t_shape **res;
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
