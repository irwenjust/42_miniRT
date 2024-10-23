/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:44:24 by likong            #+#    #+#             */
/*   Updated: 2024/10/23 12:52:02 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	save_color(char **rgb)
{
	return ((t_color){
		.red = ft_within_range(ft_atoi(rgb[R]), 0, 255),
		.green = ft_within_range(ft_atoi(rgb[G]), 0, 255),
		.blue = ft_within_range(ft_atoi(rgb[B]), 0, 255)
	});
}
