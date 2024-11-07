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

bool	save_ambient(int counter[3], char **arg, t_ambient *ambient)
{
	char	**rgb;

	if (ft_matrix_size(arg) != 3)
		return (ERROR("ambient: needs 3 arguments"), false);
	//more check here
		//validate_arg(); //TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//brightness
	ambient->brightness = ft_atod(arg[1]);
	if (ambient->brightness < 0.0 || ambient->brightness > 1.0)
		return (ERROR("ambient: error in lighting ratio range"), false);
	//rgb
	rgb = ft_split(arg[2], ',');
	if (!rgb)
		return (ERROR("ambient: error in split color"), false);
	ambient->color = save_color(rgb);
	//count
	counter[0]++;
	//clean
	free_matrix(rgb);
	return (true);
}
