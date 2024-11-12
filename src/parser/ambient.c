/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:17:45 by likong            #+#    #+#             */
/*   Updated: 2024/10/23 13:34:36 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	parse_ambient(int counter[3], char **arg, t_ambient *ambient)
{
	char	**rgb;

	//check
	if (ft_matrix_size(arg) != 3)
		return (ERROR("ambient: needs 3 arguments"), false);
	if (!check_syntax(arg, "001"))
		return (ERROR("ambient: Misconfiguration in commas/numbers"), false);
	//check brightness
	ambient->brightness = ft_atod(arg[1]);
	if (ambient->brightness < 0.0 || ambient->brightness > 1.0)
		return (ERROR("ambient: error in lighting ratio range"), false);
	//check rgb
	if (!check_rgb(arg[2]))
		return (ERROR("ambient: error in color"), false);
	rgb = ft_split(arg[2], ',');
	if (!rgb)
		return (ERROR("ambient: error in split color"), false);
	ambient->color = save_color(rgb); //之后会用吗，可以改成arg[2]吗
	//count and clean
	counter[0]++;
	free_matrix(rgb);
	
	return (true);
}
