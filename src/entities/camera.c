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

bool	save_camera(int counter[3], char **tmp, t_camera *camera)
{
	char	**pos;
	char	**normal;

	if (ft_matrix_size(tmp) != 4)
		return (ERROR("camera needs 4 arguments"), false);
	//miss syntax check
	pos = ft_split(tmp[1], ',');
	normal = ft_split(tmp[2], ',');
	camera->coordinate = save_vector(pos);
	camera->normal = normalize_vector(save_vector(normal));
	free_matrix(pos);
	free_matrix(normal);
	if (vector_len(camera->normal) < 1e-8)
		return (ERROR("normal vector is too small in camera"), false);
	camera->fov = ft_atoi(tmp[3]);
	if (camera->fov < 0 || camera->fov > 180)
		return (ERROR("normal vector's visual is out of range"), false);
	counter[1]++;
	return (camera);
}
