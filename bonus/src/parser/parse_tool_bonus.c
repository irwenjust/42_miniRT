/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tool_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzhan <yzhan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:15:54 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/14 15:16:01 by yzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_color	parse_color(char **rgb)
{
	return ((t_color){
		.red = ft_within_range(ft_atoi(rgb[0]), 0, 255),
		.green = ft_within_range(ft_atoi(rgb[1]), 0, 255),
		.blue = ft_within_range(ft_atoi(rgb[2]), 0, 255),
		.alpha = ft_within_range(0XFF, 0, 255)
	});
}
