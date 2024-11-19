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

	if (ft_matrix_size(arg) != 4 || !check_syntax(arg, "0110"))
		return (ERROR("camera: wrong args format"), false);
	coord = ft_split(arg[1], ',');
	if (!coord)
		return (ERROR("camera: fail to split coordinate"), false);
	camera->coordinate = parse_vector(coord);
	free_matrix(coord);
	normal = ft_split(arg[2], ',');
	if (!normal)
		return (ERROR("camera: fail to split normal"), false);
	camera->normal = vector_normalize(parse_vector(normal));
	free_matrix(normal);
	if (vector_magnitude(camera->normal) < 1e-8)
		return (ERROR("camera: normal vector is too small"), false);
	camera->fov = ft_atoi(arg[3]);
	if (camera->fov < 0 || camera->fov > 180)
		return (ERROR("camera: normal vector's visual is out of range"), false);
	counter[1]++;
	return (camera);
}
