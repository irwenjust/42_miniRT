/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:55:29 by yzhan             #+#    #+#             */
/*   Updated: 2025/02/18 10:29:02 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	check_rgb(char *rgb)
{
	int		i;
	bool	valid;
	char	**token;

	i = -1;
	valid = true;
	token = ft_split(rgb, ',');
	if (!token)
		return (error("check rgb: split error"), false);
	while (token[++i])
	{
		if (!ft_isnum(token[i]))
			valid = false;
		if (ft_atoi(token[i]) < 0 || ft_atoi(token[i]) > 255)
			valid = false;
		if (!valid)
			break ;
	}
	free_matrix(token);
	if (!valid)
		return (error("check rgb: wrong rgb number"), false);
	return (valid);
}

t_color	parse_color(char **rgb)
{
	return ((t_color){
		.red = ft_within_range(ft_atoi(rgb[0]), 0, 255),
		.green = ft_within_range(ft_atoi(rgb[1]), 0, 255),
		.blue = ft_within_range(ft_atoi(rgb[2]), 0, 255),
		.alpha = ft_within_range(0XFF, 0, 255)
	});
}
