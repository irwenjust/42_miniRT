/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: likong <likong@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:28:51 by likong            #+#    #+#             */
/*   Updated: 2024/10/23 18:27:49 by likong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	parse_camera(int counter[3], char **arg, t_camera *camera)
{
	char	**coord;
	char	**normal;

	if (ft_matrix_size(arg) != 4)
		return (ERROR("camera: needs 4 arguments"), false);
	//miss syntax check
		//validate_arg(); //TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (!check_syntax(arg, "0110"))
		return (ERROR("camera: Misconfiguration in commas/numbers"), false);
	//coord
	coord = ft_split(arg[1], ',');
		//check coord TODO
	camera->coordinate = save_vector(coord);
	//normal
	normal = ft_split(arg[2], ',');
		//check normal TODO	
	camera->normal = normalize_vector(save_vector(normal));
	if (vector_len(camera->normal) < 1e-8)
		return (ERROR("camera: normal vector is too small"), false);
	//fov
	camera->fov = ft_atoi(arg[3]);
	if (camera->fov < 0 || camera->fov > 180)
		return (ERROR("camera: normal vector's visual is out of range"), false);
	//count
	counter[1]++;
	//clean
	free_matrix(coord);
	free_matrix(normal);
	return (camera);
}
