/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:22:53 by likong            #+#    #+#             */
/*   Updated: 2024/11/26 15:45:45 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bvh	*init_bvh()
{
	t_bvh	*res;

	if (!s()->shapes)
		return (NULL);
	res = ft_calloc(1, sizeof(t_bvh));
	if (!res)
		return (NULL);
	res->id = 
	return (res);
}
