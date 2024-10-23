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

bool	save_ambient(int counter[3], char **tmp, t_ambient *ambient)
{
	char	**rgb;

	if (ft_matrix_size(tmp) != 3)
		return (ERROR("ambient needs 3 arguments"), false);
	//more check here
	if (ft_atod(tmp[1]) < 0.0 || ft_atod(tmp[1]) > 1.0)
		return (ERROR("error happend in lighting ratio range"), false);
	rgb = ft_split(tmp[2], ',');
	if (!rgb)
		return (ERROR("error happend in split ambient color"), false);
	ambient->brightness = ft_atod(tmp[1]);
	ambient->color = save_color(rgb);
	free_matrix(rgb);
	counter[0]++;
	return (true);
}
